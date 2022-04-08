#include <stdio.h>
#include <time.h>

#include <vector>
#include <unordered_map>

bool rand_list(int n, int k, std::vector<int>& results) {
    if (n <= 0 || k <= 0) { return false; }
    unsigned int M = 2147483647;
    unsigned int A = 48271;
    unsigned int C = 0;
    unsigned int R1 = time(NULL);
    unsigned int R2 = 0;
    for (int i = 0; i < k; i++) {
        R2 = (A * R1 + C) % M;
        R1 = R2;
        results.push_back(R2 % n);
    }
    return true;
}

int main() {
    std::vector<int> results;
    int n = 100;
    int k = 10000;
    rand_list(n, k, results);
    std::unordered_map<int, int> num_map;
    for (auto r : results) {
        if (num_map.find(r) == num_map.end()) {
            num_map[r] = 0;
        }
        num_map[r] += 1;
    }
    for (int i = 0; i < n; i++) {
        if (num_map.find(i) == num_map.end()) {
            printf("[%u]: count[%d]\n", i, 0);
            continue;
        }
        printf("[%u]: count[%d]\n", i, num_map[i]);
    }
    return 0;
}