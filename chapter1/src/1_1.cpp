#include <stdio.h>
#include <time.h>

#include <random>
#include <set>

/**
 * @brief Use std::set to order numbers.
 */
int main() {
    int count = 1000000;
    std::set<int> num_set;

    std::random_device dev;
    std::mt19937 generator(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0UL, 10000000UL);

    // # Get begin time.
    struct timespec begin;
    clock_gettime(CLOCK_REALTIME, &begin);

    for (int i = 0; i < count; ++i) {
        num_set.insert(dist(generator));
    }

    // Get end time.
    struct timespec end;
    clock_gettime(CLOCK_REALTIME, &end);

    // Calculate timecost.
    long time_cost_ns = (end.tv_sec - begin.tv_sec) * 1000000000UL + end.tv_nsec - begin.tv_nsec;
    double time_cost_ms = time_cost_ns * 1.0 / 1000000;
    printf("[%d] numbers sorted ok, cost[%.3lfms]\n", count, time_cost_ms);

    return 0;
}