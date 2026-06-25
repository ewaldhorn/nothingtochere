library basic_canvas;

// 1. Import JavaScript functions from the host environment
// We tell the compiler these exist outside the Wasm module in the 'env' namespace.
procedure fillRect(x, y, w, h: Integer); external 'env' name 'fillRect';
procedure clearRect(x, y, w, h: Integer); external 'env' name 'clearRect';

// Global state for our animation
var
  boxX: Integer = 0;

// 2. Export our render loop so JavaScript can call it
procedure renderFrame(canvasWidth, canvasHeight: Integer); export;
begin
  // Clear the previous frame
  clearRect(0, 0, canvasWidth, canvasHeight);
  
  // Draw a moving rectangle
  fillRect(boxX, 50, 100, 100);
  
  // Update state
  boxX := boxX + 2;
  if boxX > canvasWidth then
    boxX := -100; // Reset off-screen
end;

exports
  renderFrame name 'renderFrame';

begin
end.
