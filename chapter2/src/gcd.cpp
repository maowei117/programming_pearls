#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    if (a == 0 || b == 0) { return 0; }
    while (true) {
        a %= b;
        if (a == 0) { return b; }

        b %= a;
        if (b == 0) { return a;}
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) { 
        printf("Usage: %s <a> <b>\n", argv[0]);
        return 1;
    }
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int ab_gcd = gcd(a, b);
    printf("GCD for %d and %d = %d\n", a, b, ab_gcd);
    return 0;
}