#include <vector>
#include <numeric>
#include <algorithm>

#define WASM_EXPORT __attribute__((visibility("default"))) extern "C"

WASM_EXPORT int processNumbers(int* input, int length) {
    if (length <= 0) return 0;

    std::vector<int> data(input, input + length);
    std::reverse(data.begin(), data.end());

    return std::accumulate(data.begin(), data.end(), 0);
}
