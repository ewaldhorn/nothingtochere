// Ref: https://nullprogram.com/blog/2023/06/26/
// This is free and unencumbered software released into the public domain.
#include <chrono>
#include <iostream>
#include <map>
#include <stdint.h>
#include <vector>

typedef struct {
    int16_t i, j;
    bool ok;
} TwoSum;

static TwoSum twosum_map(std::vector<int32_t>& nums, int32_t target)
{
    TwoSum r = {};
    std::map<int32_t, int16_t> seen;
    for (int16_t i = 0; static_cast<size_t>(i) < nums.size(); i++) {
        int32_t complement = target - nums[i];
        if (seen.count(complement)) {
            r.i = seen[complement];
            r.j = i;
            r.ok = true;
            return r;
        }
        seen[nums[i]] = i;
    }
    return r;
}

static TwoSum twosum_bespoke(int32_t *nums, int16_t count, int32_t target)
{
    TwoSum r = {};
    int16_t seen[1<<14] = {0};
    for (int16_t n = 0; n < count; n++) {
        int32_t number = nums[n];
        int32_t complement = target - number;
        int32_t key = complement>number ? complement : number;
        uint32_t hash = key * 489183053u;
        unsigned mask = sizeof(seen)/sizeof(*seen) - 1;
        unsigned step = hash>>16 | 1;
        for (unsigned i = hash;;) {
            i = (i + step) & mask;
            int16_t j = seen[i] - 1;
            if (j < 0) {
                seen[i] = n + 1;
                break;
            } else if (nums[j] == complement) {
                r.i = j;
                r.j = n;
                r.ok = true;
                return r;
            }
        }
    }
    return r;
}

static int32_t rand31(std::uint64_t *rng)
{
    *rng = *rng*0x3243f6a8885a308d + 1;
    return static_cast<int32_t>(*rng >> 33);
}

static std::vector<int32_t> newnums(std::uint64_t *rng)
{
    std::vector<int32_t> nums(10000);
    for (int i = 0; i < 10000; i++) {
        nums[i] = rand31(rng) % 1000000000;
    }
    return nums;
}

static std::tuple<int16_t, int16_t> newtarget(std::uint64_t *rng)
{
    for (;;) {
        int16_t i = static_cast<int16_t>(rand31(rng) % 10000);
        int16_t j = static_cast<int16_t>(rand31(rng) % 10000);
        if (i != j) {
            return {i, j};
        }
    }
}

int main()
{
    int runs = 1000;
    unsigned sum = 0;
    uint64_t rng = 1;
    auto nums = newnums(&rng);

    rng = 0;
    auto start = std::chrono::high_resolution_clock::now();
    for (int n = 0; n < runs; n++) {
        auto [i, j] = newtarget(&rng);
        auto r = twosum_map(nums, nums[i]+nums[j]);
        sum += r.i;
        sum += r.j;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    std::cout << "map\t" << (stop - start).count() << std::endl;

    rng = 0;
    start = std::chrono::high_resolution_clock::now();
    for (int n = 0; n < runs; n++) {
        auto [i, j] = newtarget(&rng);
        int16_t count = static_cast<int16_t>(nums.size());
        auto r = twosum_bespoke(nums.data(), count, nums[i]+nums[j]);
        sum += r.i;
        sum += r.j;
    }
    stop = std::chrono::high_resolution_clock::now();
    std::cout << "bespoke\t" << (stop - start).count() << std::endl;

    volatile unsigned sink = sum;
    (void)sink;
    return 0;
}
