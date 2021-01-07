#ifndef TUPLE_HEADER
#define TUPLE_HEADER

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct Tuple {
    float x;
    float y;
    float z;
    float w;
} Tuple;

void printTuple( Tuple t) {
    printf("  x: %f\n", t.x );
    printf("  y: %f\n", t.y );
    printf("  z: %f\n", t.z );
    printf("  w: %f\n", t.w );
};

Tuple createTuple(float x, float y, float z, float w) {
    Tuple tuple = { x, y, z, w };
    return tuple;
}

Tuple createPoint(float x, float y, float z){
    return createTuple(x, y, z, 1);
}

Tuple createVector(float x, float y, float z){
    return createTuple(x, y, z, 0);
}

bool isPoint(Tuple tuple) {
    return tuple.w == 1;
}
bool isVector(Tuple tuple) {
    return tuple.w == 0;
}

bool equals(Tuple a, Tuple b) {
    const float EPSILON = 0.00001;
    return fabs(a.x - b.x) < EPSILON  
        && fabs(a.y - b.y) < EPSILON
        && fabs(a.z - b.z) < EPSILON
        && fabs(a.w - b.w) < EPSILON;
}

Tuple add(Tuple a, Tuple b){
    return createTuple(
        a.x + b.x,
        a.y + b.y,
        a.z + b.z,
        a.w + b.w
    );
};

Tuple subtract(Tuple a, Tuple b){
    return createTuple(
        a.x - b.x,
        a.y - b.y,
        a.z - b.z,
        a.w - b.w
    );
};

Tuple negate(Tuple a) {
    return createTuple(
        -a.x,
        -a.y,
        -a.z,
        -a.w
    );
}

Tuple multiply(Tuple a, float num) {
    return createTuple(
        a.x * num,
        a.y * num,
        a.z * num,
        a.w * num
    );
}

Tuple divide(Tuple a, float num) {
    return createTuple(
        a.x / num,
        a.y / num,
        a.z / num,
        a.w / num
    );
}

float magnitude(Tuple a) {
    float powX = pow(a.x, 2);
    float powY = pow(a.y, 2);
    float powZ = pow(a.z, 2);
    float powW = pow(a.w, 2);
    return sqrt(powX + powY + powZ + powW);
}

Tuple normalize(Tuple a) {
    float mag = magnitude(a);
    return createTuple(
        a.x / mag,
        a.y / mag,
        a.z / mag,
        a.w / mag
    );
}

float dot(Tuple a, Tuple b) {
    return a.x * b.x +
        a.y * b.y +
        a.z * b.z +
        a.w * b.w;
};

Tuple cross(Tuple a, Tuple b) {
    return createVector(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
};

#endif
