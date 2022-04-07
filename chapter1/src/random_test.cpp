#include <stdio.h>

#include <algorithm>
#include <random>

int main() {
    int count = 10;
    std::random_device rd;
    printf("random_device generator, rd.max:%u rd.min:%u\n", rd.max(), rd.min());
    for (int i = 0; i < count; ++i) {
        printf("%u\t", rd());
    }
    printf("\n");

    return 0;
}