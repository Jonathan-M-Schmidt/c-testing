#ifndef CANVAS_HEADER
#define CANVAS_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "../color/color.c"
#include "../helpers/clamp.c"

typedef struct Canvas {
    int width;
    int height;
    Color colors[];
} Canvas;

Canvas* createCanvas(int width, int height) {
    int ratio = width * height;
    // dynamically allocate memory for colors array size
    Canvas *c = malloc(sizeof(Canvas) + (ratio * sizeof(Color)));
    if (!c) { perror("malloc canvas size"); exit(EXIT_FAILURE); };
    c->width = width;
    c->height = height;
    for( int i = 0; i < ratio; i++ ) {
        c->colors[i] = createColor(0, 0, 0);
    }
    return c;
};

void writePixel(Canvas *canvas, int x, int y, Color color) {
    int position = canvas->width * (y-1) + (x-1);
    canvas->colors[position] = color;
}

Color pixelAt(Canvas *canvas, int x, int y) {
    int position = canvas->width * (y-1) + (x-1);
    Color color = canvas->colors[position];
    return color;
}

void canvasToPpm(Canvas *canvas, char *fileName) {
    char cwd[1024] = {0};
    getcwd(cwd, sizeof(cwd));
    char finalPath[1024] = {0};
    strcat(finalPath, cwd);
    strcat(finalPath, "\\img\\");
    strcat(finalPath, fileName);
    strcat(finalPath, ".ppm");
    FILE *fptr = fopen(finalPath, "w");
    if(fptr == NULL)
    {
        printf("Error!\n");
        perror("open file: ");
        exit(1);             
    }
    fprintf(fptr, "P3\n");
    fprintf(fptr, "%i %i\n", canvas->width, canvas->height);
    fprintf(fptr, "255\n\n");
    int count = 0;
    for(int i = 0; i < (canvas->width*canvas->height); i++) {
        int red = round(canvas->colors[i].red * 255);
        int green = round(canvas->colors[i].green * 255);
        int blue = round(canvas->colors[i].blue * 255);
        printf("formatted color value red: %i\n", red);
        printf("formatted color value green: %i\n", green);
        printf("formatted color value blue: %i\n", blue);
        int red_c = clamp(red, 0, 255);
        int green_c = clamp(green, 0, 255);
        int blue_c = clamp(blue, 0, 255);
        printf("clamped color value red: %i\n", red_c);
        printf("clamped color value green: %i\n", green_c);
        printf("clamped color value blue: %i\n", blue_c);
        fprintf(fptr, "%i %i %i ", red_c, green_c, blue_c);
        printf("modulo: %i index: %i\n", i%(canvas->width-1), i);
        if ( count == canvas->width-1 ) {
            count = 0;
            fprintf(fptr, "\n");
        } else {
            count++;
        }
    }
    fclose(fptr);
    printf("canvas saved as image at: %s\n", finalPath);
};

#endif
