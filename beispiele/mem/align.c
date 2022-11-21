#include <stdio.h>

struct Pixel {
    unsigned char r, g, b;
};

int main() {
    struct Pixel pixel1;
    struct Pixel pixel2;

    struct Pixel image[8*8];

    printf("Groesse struct Pixel: %d\n", sizeof(struct Pixel));
    printf("Adresse Pixel 1: %ul\n", &pixel1);
    printf("Adresse Pixel 2: %ul\n", &pixel2);

    printf("Adresse image[0]: %ul\n", &image[0]);
    printf("Adresse image[1]: %ul\n", &image[1]);
}