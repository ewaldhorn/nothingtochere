# WASM and EmScripten

Run `emcc -O1 ./sum.cpp -o sum.html -sWASM=0 -sEXPORTED_FUNCTIONS='["_sum"]'`

Open `sum.html` in a browser and run `ccall("sum", "number", "number, number", [10, 20])` to execute.
