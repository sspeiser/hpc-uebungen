#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <sys/timeb.h>

uint64_t system_current_time_millis()
{
#if defined(_WIN32) || defined(_WIN64)
    struct _timeb timebuffer;
    _ftime(&timebuffer);
    return (uint64_t)(((timebuffer.time * 1000) + timebuffer.millitm));
#else
    struct timeb timebuffer;
    ftime(&timebuffer);
    return (uint64_t)(((timebuffer.time * 1000) + timebuffer.millitm));
#endif
}


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

    // Zeitmessen Start
    uint64_t start = system_current_time_millis();

    // TODO Konvertierung

    // Zeitmessen Ende
    uint64_t end = system_current_time_millis();
    double sec = (end - start) / 1.0e3;
    printf("%8.6f seconds\n", sec);

    // TODO FLOP Berechnung

    //TODO Ausgabe FLOP/s

    stbi_write_jpg("grayscale.jpg", width, height, 1, gray, 95);
}