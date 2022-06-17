#include <stdio.h>

int gcd(int a, int b) {
    if (a == 0 || b == 0) { return 0; }
    while (true) {
        a %= b;
        if (a == 0) { return b; }

        b %= a;
        if (b == 0) { return a;}
    }
}

bool left_rorate_shift(char* a, int n, int i) {
    /*
    char temp = '\0';

    int round = n / i;
    for (int index = 0; index < i; index++) {
        // Move a[index] -> temp;
        // Move a[index + i] -> a[index];
        // ...
        // Move a[index + k * i] -> a[index + (k - 1) * i];
        // Stop when (index + k * i) % n == index
    }
    */
    return true;
}

bool left_rotate_bisection(char* a, int n, int i) {
    return true;
}

bool left_rotate_inversion(char* a, int n, int i) {
    return true;
}

int main(int argc, char* argv[]) {
    char array[27] = "abcdefghijklmnopqrstuvwxyz";
    printf("Origin array:%s\n", array);

    int n = 26;
    int i = 3;

    // Shift rotate.
    char array1[27] = "abcdefghijklmnopqrstuvwxyz";
    left_rorate_shift(array1, n, i);
    printf("After shift rotate:%s\n", array1);

    // Bisection rotate.
    char array2[27] = "abcdefghijklmnopqrstuvwxyz";
    left_rotate_bisection(array2, n, i);
    printf("After bisection rotate:%s\n", array2);

    // Inversion rotate.
    char array3[27] = "abcdefghijklmnopqrstuvwxyz";
    left_rotate_inversion(array3, n, i);
    printf("After inversion rotate:%s\n", array3);
    return 0;
}