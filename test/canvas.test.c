#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../canvas/canvas.c"
#include "../color/color.c"
#include "../test-frame/test-frame.c"

int testCanvasCreation() {
    Canvas *canvas = createCanvas(10, 20);
    expect(canvas->width == 10, "canvas should have correct width");
    expect(canvas->height == 20, "canvas should have correct height");
    Color res = createColor(0,0,0);
    for(int i = 0; i < (canvas->width * canvas->height); i++) {
        expect(equals_c(res, canvas->colors[i]), "all colors should initialize correct");
    }
};

int testWriteAndReadPixelToCanvas() {
    Canvas *canvas = createCanvas(10, 20);
    Color red = createColor(1, 0, 0);
    writePixel(canvas, 2, 3, red);
    Color result = pixelAt(canvas, 2, 3);
    expect(equals_c(red, result), "write and read correct color from canvas");
};

int testPpmHeaderCreation() {
    Canvas *canvas = createCanvas(5, 3);
    canvasToPpm(canvas, "testing");
    char ppm[1024] = {0};
    FILE *fptr;

    if ((fptr = fopen("F:\\prog\\c\\ray-tracer\\img\\testing.ppm","r")) == NULL){
        printf("Error! opening file");
        exit(1);
    }
    for(int i = 0; i < 4; i++) {
        char temp[255] = {0};
        fgets(temp, sizeof(temp), fptr);
        strcat(ppm, temp);
    }

    fclose(fptr);

    expect(strcmp(ppm,"P3\n5 3\n255\n\n") == 0, "creates correct header");
};

int testPpmPixelDataCreation() {
    Canvas *canvas = createCanvas(5, 3);
    Color color1 = createColor(1.5, 0, 0);
    Color color2 = createColor(0, 0.5, 0);
    Color color3 = createColor(-0.5, 0, 1);
    writePixel(canvas, 1, 1, color1);
    writePixel(canvas, 3, 2, color2);
    writePixel(canvas, 5, 3, color3);
    canvasToPpm(canvas, "testing");
    char ppm[1024];
    FILE *fptr;

    if ((fptr = fopen("F:\\prog\\c\\ray-tracer\\img\\testing.ppm","r")) == NULL){
        printf("Error! opening file");
        exit(1);
    }

    fread(ppm, 1024, 1, fptr);

    char expected[] = "P3\n5 3\n255\n\n255 0 0 0 0 0 0 0 0 0 0 0 0 0 0 \n0 0 0 0 0 0 0 128 0 0 0 0 0 0 0 \n0 0 0 0 0 0 0 0 0 0 0 0 0 0 255 \n";

    fclose(fptr);

    expect(strcmp(ppm, expected) == 0, "creates correct pixel data");
};

int testSplittingLongLines() {
    Canvas *canvas = createCanvas(10, 2);
    for(int y = 1; y<= 2; y++){
        for(int x = 1; x<=10; x++){
            writePixel(canvas, x, y, createColor(1, 0.8, 0.6));
        }
    }
    canvasToPpm(canvas, "line_splitting");
    char ppm[1024] = {0};
    FILE *file_res;

    if ((file_res = fopen("F:\\prog\\c\\ray-tracer\\img\\line_splitting.ppm","r")) == NULL){
        printf("Error! opening file");
        exit(1);
    }

    fread(ppm, 1024, 1, file_res);

    char ppm_expected[1024] = {0};
    FILE *file_res_expected;

    if ((file_res_expected = fopen("F:\\prog\\c\\ray-tracer\\test\\line_splitting_expected.ppm","r")) == NULL){
        printf("Error! opening file");
        exit(1);
    }

    fread(ppm_expected, 1024, 1, file_res_expected);

    expect(strcmp(ppm, ppm_expected) == 0, "creates correct line breaks");
}

int main() {;
    runTestSuit(
        "should create correct canvas with default colors\n",
        testCanvasCreation
    );
    runTestSuit(
        "should write and read pixel to/from canvas\n",
        testWriteAndReadPixelToCanvas
    );
    runTestSuit(
        "should create correct ppm header from canvas\n",
        testPpmHeaderCreation
    );
    runTestSuit(
        "should create correct ppm pixel data from canvas\n",
        testPpmPixelDataCreation
    );
    runTestSuit(
        "should split lines when over 70 chars\n",
        testSplittingLongLines
    );
    
    finishTests();
}