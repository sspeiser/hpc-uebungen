#include <stdlib.h>
#include <stdio.h>

// Works correctly without restrict - error with restrict
int shift(int* restrict a, int* restrict b , int n) {
    for(int i=1; i<n; i++) {
        a[i] = b[i-1];
    }
    return a[n-1];
}

int main() {
    int* a = malloc(sizeof(int) * 1024);
    // int* b = malloc(sizeof(int) * 1024);
    int* b = a;
    int n = 1024;
    for(int i = 0; i < n; i ++) {
        a[i] = 0;
        b[i] = 0;
    }
    b[0] = 1000;
    b[n-2] = 2000;

    int result = shift(a, b, n);
    printf("%d\n", result);
}
