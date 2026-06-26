// bouncer.js — JS/WASM glue for Pascal Bouncer
// Loads the compiled WASM module and bridges to the browser canvas

(async () => {
    "use strict";

    let wasmModule = null;
    let wasmMemory = null;
    let wasmBuffer = null;
    let canvas = null;
    let ctx = null;
    let animationFrameId = null;
    let lastTime = performance.now();
    let keepRunning = false;

    // Scoreboard elements
    const scoreVal = document.getElementById('score-val');
    const areaVal = document.getElementById('area-val');
    const livesVal = document.getElementById('lives-val');
    const levelVal = document.getElementById('level-val');
    const finalScoreVal = document.getElementById('final-score-val');
    const nextLevelVal = document.getElementById('next-level-val');

    // Overlay elements
    const startScreen = document.getElementById('start-screen');
    const gameOverScreen = document.getElementById('game-over-screen');
    const levelCompleteScreen = document.getElementById('level-complete-screen');

    // Game states (matching Pascal TGameStatus enum)
    const StartScreen = 0;
    const Playing = 1;
    const GameOver = 2;
    const LevelUpDelay = 3;

    // WASM exports
    let exports = null;

    function getExport(name) {
        if (!exports) throw new Error(`WASM exports not loaded`);
        const fn = exports[name];
        if (!fn) throw new Error(`Export '${name}' not found in WASM module`);
        return fn;
    }

    // Read a string from WASM memory (null-terminated)
    function readString(ptr) {
        const bytes = [];
        let i = 0;
        while (true) {
            const byte = wasmBuffer[ptr + i];
            if (byte === 0) break;
            bytes.push(byte);
            i++;
        }
        return String.fromCharCode(...bytes);
    }

    // Read an integer (32-bit signed) from WASM memory
    function readInt32(ptr) {
        return new Int32Array(wasmMemory.buffer, ptr, 1)[0];
    }

    // Read a float (64-bit) from WASM memory
    function readFloat64(ptr) {
        return new Float64Array(wasmMemory.buffer, ptr, 1)[0];
    }

    // Write a string to WASM memory (caller must allocate enough space)
    function writeString(str, ptr) {
        for (let i = 0; i < str.length; i++) {
            wasmBuffer[ptr + i] = str.charCodeAt(i);
        }
        wasmBuffer[ptr + str.length] = 0;
    }

    // Helper to read a Pascal string from a pointer
    function readPascalString(ptr) {
        // Pascal string: first byte is length, then characters
        const len = wasmBuffer[ptr];
        const chars = [];
        for (let i = 0; i < len; i++) {
            chars.push(wasmBuffer[ptr + 1 + i]);
        }
        return String.fromCharCode(...chars);
    }

    // Tell Pascal where to draw — fixed offset past all static data
    function setupCanvas() {
        const w = canvas.width;
        const h = canvas.height;
        // Use a fixed safe offset (256 KB = 0x40000), well past static
        // data segments which end around 104 KB.  1200*750*4 = 3.6 MB
        // fits comfortably in the 4 MB initial memory.
        const pixelsPtr = 256 * 1024;
        getExport('CanvasInit')(w, h, pixelsPtr, 0);
        return pixelsPtr;
    }

    // Initialize the WASM module
    async function initWasm() {
        const response = await fetch('bouncer.wasm');
        const buffer = await response.arrayBuffer();

        // Provide _haltproc import required by FPC embedded target
        const importObject = {
            env: {
                _haltproc: (exitCode) => {
                    console.log(`Pascal halted with code: ${exitCode}`);
                    keepRunning = false;
                }
            }
        };

        wasmModule = await WebAssembly.instantiate(buffer, importObject);
        wasmMemory = wasmModule.instance.exports.memory;
        wasmBuffer = new Uint8Array(wasmMemory.buffer);
        exports = wasmModule.instance.exports;

        // Call Pascal's init
        getExport('init')();
    }

    // Render the game frame
    function render() {
        const renderFn = getExport('render');
        if (renderFn) {
            renderFn();
        }

        // Copy the pixel buffer to the canvas
        if (canvas && ctx) {
            const width = getExport('get_width')();
            const height = getExport('get_height')();
            const pixelsPtr = getExport('get_pixels')();

            // The pixel buffer is a Uint8ClampedArray in WASM memory
            // Each pixel is 4 bytes (RGBA)
            const imageData = ctx.createImageData(width, height);
            const data = new Uint8ClampedArray(wasmMemory.buffer, pixelsPtr, width * height * 4);
            imageData.data.set(data);
            ctx.putImageData(imageData, 0, 0);
        }
    }

    // Update the scoreboard UI
    function updateUI() {
        const score = getExport('get_score')();
        const lives = getExport('get_lives')();
        const level = getExport('get_level')();
        const status = getExport('get_game_status')();
        const percent = getExport('get_percent_captured')();

        scoreVal.textContent = String(score).padStart(6, '0');
        areaVal.textContent = percent.toFixed(1) + '%';
        livesVal.textContent = lives;
        levelVal.textContent = level;

        // Handle overlays
        switch (status) {
            case StartScreen:
                startScreen.classList.remove('hidden');
                gameOverScreen.classList.add('hidden');
                levelCompleteScreen.classList.add('hidden');
                break;
            case Playing:
                startScreen.classList.add('hidden');
                gameOverScreen.classList.add('hidden');
                levelCompleteScreen.classList.add('hidden');
                break;
            case GameOver:
                startScreen.classList.add('hidden');
                gameOverScreen.classList.remove('hidden');
                levelCompleteScreen.classList.add('hidden');
                finalScoreVal.textContent = score;
                break;
            case LevelUpDelay:
                startScreen.classList.add('hidden');
                gameOverScreen.classList.add('hidden');
                levelCompleteScreen.classList.remove('hidden');
                nextLevelVal.textContent = level + 1;
                break;
        }
    }

    // Handle key events
    function handleKeyDown(e) {
        const key = e.keyCode || e.which;

        // Enter/Space to start/restart — works even when game loop isn't running yet
        if (key === 13 || key === 32) {
            e.preventDefault();
            if (getExport('get_game_status')() === StartScreen ||
                getExport('get_game_status')() === GameOver) {
                getExport('on_start')();
                keepRunning = true;
                lastTime = performance.now();
                animationFrameId = requestAnimationFrame(tick);
            }
            return;
        }

        // Arrow keys for player movement — only during gameplay
        if (!keepRunning) return;
        if (key >= 37 && key <= 40) {
            e.preventDefault();
            getExport('on_key_down')(key);
        }
    }

    // Game loop
    function tick() {
        const now = performance.now();
        const deltaTime = (now - lastTime) / 1000.0; // seconds
        lastTime = now;

        // Call Pascal's step function (expects seconds)
        const stepFn = getExport('step');
        if (stepFn) {
            stepFn(deltaTime);
        }

        // Render the frame
        render();

        // Update UI
        updateUI();

        if (keepRunning) {
            animationFrameId = requestAnimationFrame(tick);
        } else {
            animationFrameId = null;
        }
    }

    // Initialize everything
    async function init() {
        try {
            await initWasm();

            // Get canvas element
            canvas = document.getElementById('game-canvas');
            ctx = canvas.getContext('2d');

            // Tell Pascal about the canvas pixel buffer
            setupCanvas();

            // Set up event listeners
            window.addEventListener('keydown', handleKeyDown);

            // Start button
            document.getElementById('start-button').addEventListener('click', () => {
                if (getExport('get_game_status')() === StartScreen ||
                    getExport('get_game_status')() === GameOver) {
                    getExport('on_start')();
                    keepRunning = true;
                    lastTime = performance.now();
                    animationFrameId = requestAnimationFrame(tick);
                }
            });

            // Restart button
            document.getElementById('restart-button').addEventListener('click', () => {
                getExport('on_start')();
                keepRunning = true;
                lastTime = performance.now();
                animationFrameId = requestAnimationFrame(tick);
            });

            // Initial render
            updateUI();

        } catch (e) {
            console.error('Failed to initialize WASM:', e);
        }
    }

    // Start the game
    init();
})();
