#include <stdio.h>

#include <random>
#include <set>

/**
 * @brief Use std::set to order numbers.
 */
int main() {
    int count = 100;
    std::set<int> num_set;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0UL, 10000000UL);
    for (int i = 0; i < count; ++i) {
        num_set.insert(dist(rng));
    }

    int counter = 0;
    for (auto iter = num_set.cbegin(); iter != num_set.cend(); iter++) {
        printf("%d\t", *iter);
        if (++counter % 10 == 0) {
            printf("\n");
        }
    }

    return 0;
}