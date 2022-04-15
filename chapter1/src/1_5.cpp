#include <stdio.h>

#include <algorithm>
#include <random>
#include <vector>

#include "BitSet.h"

/**
 * @brief BitSet sort limit memory no more than 1MB.
 * 
 * @return int 
 */
int main() {
    int count = 100;
    int max_nums_per_round = 8 * (1 << 20);
    BitSet bs(max_nums_per_round);

    // Random set bitset.
    int max_num = 10000000;
    std::random_device dev;
    std::mt19937 generator(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, max_num);

    // Simulate input.
    std::vector<int> inputs;
    for (int i = 0; i < count; i++) {
        inputs.push_back(dist(generator));
    }

    std::vector<int> outputs;
    int round = (max_num / max_nums_per_round) + 1;
    for (int i = 0; i < round; i++) {
        int begin = i * max_nums_per_round;
        int end = (i + 1) * max_nums_per_round;
        for (auto num : inputs) {
            if (num >= begin && num < end) {
                bs.set(num - begin);
            }
        }

        // Add output.
        for (int j = 0; j < max_nums_per_round; j++) {
            if (bs.test(j)) {
                outputs.push_back(j + begin);
            }
        }
    }

    // Print results.
    for (int i = 0; i < static_cast<int>(outputs.size()); i++) {
        printf("%d\t", outputs[i]);
        if (i % 10 == 9) {
            printf("\n");
        } 
    }

    return 0;
}