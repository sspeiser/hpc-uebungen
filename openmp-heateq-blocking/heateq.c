#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define X 16384UL
#define Y 16384UL

#define PADX 64

#define A(arr, y, x) arr[x + y * (X + PADX)]

// #define TILESX 4
// #define TILESY 3

// #define TILE_W ceil(X / TILESX)
// #define TILE_H ceil(Y / TILESY)

#define TILE_W 64
#define TILE_H 64
#define TILESX ((unsigned long)ceil(X / TILE_W))
#define TILESY ((unsigned long)ceil(Y / TILE_H))

int main()
{
    size_t size = sizeof(float) * ((size_t)X + PADX) * ((size_t)Y + 2);
    printf("%zu\n", size);
    float *src_unaligned = malloc(size + 63);
    unsigned long src_first_non_ghost = (unsigned long)&A(src_unaligned, 1, 1);
    unsigned long src_first_non_ghost_aligned = (src_first_non_ghost + 63) & ~0x2F;
    float *src = (float *)((char *)src_unaligned + (src_first_non_ghost_aligned - src_first_non_ghost));

    float *dst_unaligned = malloc(size + 63);
    unsigned long dst_first_non_ghost = (unsigned long)&A(dst_unaligned, 1, 1);
    unsigned long dst_first_non_ghost_aligned = (dst_first_non_ghost + 63) & ~0x2F;
    float *dst = (float *)((char *)dst_unaligned + (dst_first_non_ghost_aligned - dst_first_non_ghost));

    for (int x = 0; x <= X + 1; x++)
    {
        for (int y = 0; y <= Y + 1; y++)
        {
            A(src, y, x) = 0.0;
        }
    }

    for (int x = 0; x <= X + 1; x++)
    {
        A(src, 0, x) = 255.0;
    }

    for (int y = 0; y <= Y + 1; y++)
    {
        A(src, y, 0) = 255.0;
    }

    for (int y = 0; y <= Y + 1; y++)
    {
        for (int x = 0; x <= X + 1; x++)
        {
            float a = A(src, y, x);
            float b = A(dst, y, x);
        }
    }

    double wtime;

    

    wtime = omp_get_wtime();
    for (int k = 0; k < 500; k++)
    {
        #pragma omp parallel for
        for (int y = 1; y < Y - 1; y++)
        {
            for (int x = 1; x < X - 1; x++)
            {
                A(dst, y, x) = 0.25 * (A(src, y, x - 1) +
                                       A(src, y, x + 1) +
                                       A(src, y - 1, x) +
                                       A(src, y + 1, x));
            }
        }
        float *tmp = src;
        src = dst;
        dst = tmp;
    }
    wtime = omp_get_wtime() - wtime;
    printf("%.2f Sekunden\n", wtime);


wtime = omp_get_wtime();

    for (int k = 0; k < 500; k++)
    {
        #pragma omp parallel for collapse(2) schedule(static,1)
        for (int tiley = 0; tiley < TILESY; tiley++)
        {
            for (int tilex = 0; tilex < TILESX; tilex++)
            {
                int starty = 1 + tiley * TILE_H;
                int endy = starty + TILE_H;
                if (endy > Y + 1)
                    endy = Y + 1;
                int startx = 1 + tilex * TILE_W;
                int endx = startx + TILE_W;
                if (endx > X + 1)
                    endx = X + 1;
                for (int y = starty; y < endy; y++)
                {
                    for (int x = startx; x < endx; x++)
                    {
                        A(dst, y, x) = 0.25 * (A(src, y, x - 1) +
                                               A(src, y, x + 1) +
                                               A(src, y - 1, x) +
                                               A(src, y + 1, x));
                    }
                }
            }
        }
        float *tmp = src;
        src = dst;
        dst = tmp;
    }
    wtime = omp_get_wtime() - wtime;
    printf("%.2f Sekunden\n", wtime);

    // char filename[20];
    //    sprintf(filename, "images/f%05i.jpg", k);
    char *filename = "pattern.jpg";
    uint8_t *img = malloc(Y * X);
    for (int y = 1; y <= Y; y++)
    {
        for (int x = 1; x <= X; x++)
        {
            img[(y - 1) * Y + x - 1] = A(dst, y, x);
        }
    }
    stbi_write_jpg(filename, X, Y, 1, img, 80);

    free(src_unaligned);
    free(dst_unaligned);
    free(img);
}