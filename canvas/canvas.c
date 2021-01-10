#ifndef CANVAS_HEADER
#define CANVAS_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "../color/color.c"
#include "../helpers/clamp.c"
#include "../helpers/len_int.c"

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


int printColorToFile(FILE *file, int color_value, int char_count ) {
    if ( char_count + len_int(color_value) + 1 < 70 ) {
        fprintf(file, "%i ", color_value);
        return char_count+(len_int(color_value)+1);
    } else {
        fprintf(file, "\n%i ", color_value);
        return 0;
    }
};

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
    int char_count = 0;
    for(int i = 0; i < (canvas->width*canvas->height); i++) {
        int red = round(canvas->colors[i].red * 255);
        int green = round(canvas->colors[i].green * 255);
        int blue = round(canvas->colors[i].blue * 255);
        int red_c = clamp(red, 0, 255);
        int green_c = clamp(green, 0, 255);
        int blue_c = clamp(blue, 0, 255);
        char_count = printColorToFile(fptr, red_c, char_count);
        char_count = printColorToFile(fptr, green_c, char_count);
        char_count = printColorToFile(fptr, blue_c, char_count);
        if ( count == canvas->width-1 ) {
            char_count=0;
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
