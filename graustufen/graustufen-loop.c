#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main()
{
    // Read color JPG into byte array "img"
    // Array contains "width" x "height" pixels each consisting of "channels" colors/bytes
    int width, height, channels;
    unsigned char *img = stbi_load("tamanna-rumee-vaTsR-ghLog-unsplash.jpg", &width, &height, &channels, 0);
    if (img == NULL)
    {
        printf("Err: loading image\n");
        exit(1);
    }

    printf("w: %d ; h: %d ; c: %d\n", width, height, channels);
    
    // Allocate target array for grayscale image
    unsigned char *gray = malloc(width * height);

    // TODO Zeitmessen Start

    // TODO Konvertierung

    // TODO Zeitmessen Ende

    // TODO FLOP Berechnung

    //TODO Ausgabe FLOP/s

    stbi_write_jpg("grayscale.jpg", width, height, 1, gray, 95);
}