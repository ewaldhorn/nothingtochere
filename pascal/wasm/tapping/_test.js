// Node.js smoke test for basic_canvas.wasm (no browser needed)
const fs = require('fs');
const wasmBytes = fs.readFileSync('basic_canvas.wasm');

const importObject = {
    env: {
        _haltproc: (exitCode) => {
            console.error('FPC halted:', exitCode);
        }
    }
};

WebAssembly.instantiate(wasmBytes, importObject).then(result => {
    const e = result.instance.exports;
    console.log('exports:', Object.keys(e).filter(k => k.startsWith('wasm_')));

    if (e.memory) {
        console.log('memory pages:', e.memory.buffer.byteLength / 65536);
    } else {
        console.log('ERROR: no memory export');
        process.exit(1);
    }

    // Check dimensions
    const w = e.wasm_get_width();
    const h = e.wasm_get_height();
    const stride = w * 4;
    console.log(`dimensions: ${w}x${h}`);

    // Init and check pixel buffer location
    e.wasm_init();
    const ptr = e.wasm_get_pixels();
    console.log('pixel buffer ptr:', ptr, `(${ptr.toString(16)})`);
    if (ptr < 65536) {
        console.log('ERROR: pixel buffer overlaps data segments');
        process.exit(1);
    }

    const avail = e.memory.buffer.byteLength;
    const needed = ptr + w * h * 4;
    if (needed > avail) {
        console.log(`ERROR: need ${needed} bytes, only ${avail} available`);
        process.exit(1);
    }
    console.log('memory OK:', needed, '<', avail);

    // Simulate a few frames and check pixel content
    const buf = new Uint8Array(e.memory.buffer, ptr, stride * h);

    // Frame 1: clear, update, draw
    e.wasm_update(0.016);

    // After update, every pixel has ClearScreen(10, 5, 20) background.
    // Check a few background pixels
    const bgR = buf[0], bgG = buf[1], bgB = buf[2], bgA = buf[3];
    console.log(`bg pixel (0,0): rgba(${bgR},${bgG},${bgB},${bgA})`);

    // Check for non-default pixels (balls drawn on top)
    // Sample the first 10 rows looking for neon-colored pixels
    let neonPixels = 0;
    for (let y = 40; y < 560; y++) {
        for (let x = 40; x < 760; x += 40) {
            const off = y * stride + x * 4;
            const r = buf[off], g = buf[off+1], b = buf[off+2];
            // Neon colors have at least one channel >= 200
            if (r >= 200 || g >= 200 || b >= 200) neonPixels++;
        }
    }
    console.log('neon pixels sampled:', neonPixels, '(should be > 0 if balls visible)');

    // Also click on canvas center to spawn a ball
    e.wasm_click(400, 300);
    e.wasm_update(0.016);
    e.wasm_update(0.016);

    // Check center area for recent spawn
    let centerNeon = 0;
    for (let y = 280; y < 320; y++) {
        for (let x = 380; x < 420; x += 10) {
            const off = y * stride + x * 4;
            const r = buf[off], g = buf[off+1], b = buf[off+2];
            if (r >= 200 || g >= 200 || b >= 200) centerNeon++;
        }
    }
    console.log('center neon pixels (after click):', centerNeon);

    if (neonPixels > 0 || centerNeon > 0) {
        console.log('SUCCESS');
    } else {
        // Check if at least the background has correct color
        if (bgR === 10 && bgG === 5 && bgB === 20) {
            console.log('WARN: background OK but no neon pixels found — balls may not be drawing');
        } else {
            console.log('FAIL: unexpected pixel values');
            process.exit(1);
        }
    }
}).catch(err => {
    console.error('FAIL:', err.message || err);
    process.exit(1);
});
