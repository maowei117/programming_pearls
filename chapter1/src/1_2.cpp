#include <stdio.h>

#include <algorithm>
#include <random>
#include <vector>

#include "BitSet.h"

int main() {
    BitSet bs(10000000UL);

    // Random set bitset.
    std::mt19937 generator;
    std::uniform_int_distribution<std::mt19937::result_type> dist(0UL, 100UL);
    std::vector<int> random_nums;
    for (int i = 0; i < 20; i++) {
        int random = dist(generator);
        bs.set(random);
        random_nums.push_back(random);
    }

    std::stable_sort(random_nums.begin(), random_nums.end());
    printf("Generate random numbers:\n");
    for (auto r : random_nums) {
        printf("%d\t", r);
    }
    printf("\n\n");

    // Test bitset.
    printf("Test bitset.\n");
    for (int i = 0; i < 101; ++i) {
        printf("%d:%d\t", i, bs.test(i));
        if ((i + 1) % 10 == 0) { printf("\n"); }
    }

    // Clear bitset.
    printf("\nClear bitset.\n");
    for (int i = 0; i < 101; ++i) {
        bs.clear(i);
    }

    // Test bitset.
    printf("\nTest bitset.\n");
    for (int i = 0; i < 101; ++i) {
        printf("%d:%d\t", i, bs.test(i));
        if ((i + 1) % 10 == 0) { printf("\n"); }
    }

    return 0;
}