#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct Tuple {
    float x;
    float y;
    float z;
    float w;
};

struct Tuple createTuple(float x, float y, float z, float w) {
    struct Tuple tuple = { x, y, z, w };
    return tuple;
}

struct Tuple createPoint(float x, float y, float z){
    return createTuple(x, y, z, 1);
}

struct Tuple createVector(float x, float y, float z){
    return createTuple(x, y, z, 0);
}

bool isPoint(struct Tuple tuple) {
    return tuple.w == 1;
}
bool isVector(struct Tuple tuple) {
    return tuple.w == 0;
}

bool equals(struct Tuple a, struct Tuple b) {
    return a.x == b.x  
        && a.y == b.y
        && a.z == b.z
        && a.w == b.w;
}

struct Tuple add(struct Tuple a, struct Tuple b){
    return createTuple(
        a.x + b.x,
        a.y + b.y,
        a.z + b.z,
        a.w + b.w
    );
};

struct Tuple subtract(struct Tuple a, struct Tuple b){
    return createTuple(
        a.x - b.x,
        a.y - b.y,
        a.z - b.z,
        a.w - b.w
    );
};

struct Tuple negate(struct Tuple a) {
    return createTuple(
        -a.x,
        -a.y,
        -a.z,
        -a.w
    );
}

struct Tuple multiply(struct Tuple a, float num) {
    return createTuple(
        a.x * num,
        a.y * num,
        a.z * num,
        a.w * num
    );
}
