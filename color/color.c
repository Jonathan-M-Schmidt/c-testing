#ifndef COLOR_HEADER
#define COLOR_HEADER

#include <stdbool.h>
#include "../tuple/tuple.c"

typedef struct Color {
    float red;
    float green;
    float blue;
} Color;

Color createColor(float red, float green, float blue) {
    Color c = {red, green, blue};
    return c;
};

struct Tuple colorToTuple(Color c){
    struct Tuple t = createTuple(c. red, c.green, c.blue, 0);
    return t;
};

Color tupleToColor(struct Tuple t) {
    Color c = createColor(t.x, t.y, t.z );
    return c;
};

Color add_c(Color a, Color b) {
    struct Tuple a_t = colorToTuple(a);
    struct Tuple b_t = colorToTuple(b);
    struct Tuple added = add(a_t, b_t);
    return tupleToColor(added);
};

Color sub_c(Color a, Color b) {
    struct Tuple a_t = colorToTuple(a);
    struct Tuple b_t = colorToTuple(b);
    struct Tuple subtracted = subtract(a_t, b_t);
    return tupleToColor(subtracted);
};

Color mul_c(Color a, float num) {
    struct Tuple a_t = colorToTuple(a);
    struct Tuple multiplied = multiply(a_t, num);
    return tupleToColor(multiplied);
};

bool equals_c(Color a, Color b) {
    struct Tuple a_t = colorToTuple(a);
    struct Tuple b_t = colorToTuple(b);
    return equals(a_t, b_t);
};

Color hadamard_product(Color a, Color b) {
    return createColor(
        a.red * b.red,
        a.green * b.green,
        a.blue * b.blue
    );
};

#endif
