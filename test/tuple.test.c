#include <stdlib.h>
#include <stdbool.h>
#include "../tuple/tuple.c"
#include "../test-frame/test-frame.c"

int testTuples() {
    struct Tuple tuple1 = createTuple(4.3, -4.2, 3.1, 1);
    expect(tuple1.x == 4.3f, "x wrong");
    expect(tuple1.y == -4.2f, "y wrong");
    expect(tuple1.z == 3.1f, "z wrong");
    expect(tuple1.w == 1, "w wrong");
    expect(isPoint(tuple1), "should be point");
    expect(!isVector(tuple1), "should not be vector");
    struct Tuple tuple2 = createTuple(4.3, -4.2, 3.1, 0);
    expect(tuple2.x == 4.3f && tuple2.y == -4.2f && tuple2.z == 3.1f && tuple2.w == 0, "wrong tuple");
    expect(isVector(tuple2), "should be vector");
}

int testFactories() {
    struct Tuple point = createPoint(4, -4, 3);
    struct Tuple tuple = createTuple(4, -4, 3, 1);
    expect(equals(point, tuple), "point should equal tuple");
    struct Tuple vector = createVector(4, -4, 3);
    struct Tuple tuple2 = createTuple(4, -4, 3, 0);
    expect(equals(vector, tuple2), "vector should equal tuple2");
}

int testAddition() {
    struct Tuple tuple1 = createTuple(3, -2, 5, 1);
    struct Tuple tuple2 = createTuple(-2, 3, 1, 0);
    struct Tuple res = createTuple(1, 1, 6, 1);
    struct Tuple added = add(tuple1, tuple2);
    expect(equals(added, res), "should add tuples");
}

int testSubtraction() {
    struct Tuple point1 = createPoint(3, 2, 1);
    struct Tuple point2 = createPoint(5, 6, 7);
    struct Tuple res = createVector(-2, -4, -6);
    struct Tuple subbed = subtract(point1, point2);
    expect(equals(subbed, res), "should subtract points and create vector");
    struct Tuple vector1 = createVector(3, 2, 1);
    struct Tuple vector2 = createVector(5, 6, 7);
    struct Tuple subbed2 = subtract(vector1, vector2);
    expect(equals(subbed2, res), "should subtract vectors");
}

int testNegation() {
    struct Tuple vector1 = createVector(0,0,0);
    struct Tuple vector2 = createVector(1, -2, 3);
    struct Tuple res = createVector(-1, 2, -3);
    struct Tuple subbed = subtract(vector1, vector2);
    expect(equals(subbed, res), "subtract vector from zero to negate");
    expect(
        equals(
            negate(vector2),
            res
        ),
        "creates correct negated vector with function"
    );
    struct Tuple tuple = createTuple(1, -2, 3, -4);
    struct Tuple res2 = createTuple(-1, 2, -3, 4);
    expect(
        equals(
            negate(tuple),
            res2
        ),
        "creates correct negated tuple with function"
    );
}

int testMultiply() {
    struct Tuple tuple = createTuple(1, -2, 3, -4);
    struct Tuple multiplied = multiply(tuple, 3.5);
    struct Tuple res = createTuple(3.5, -7, 10.5, -14);
    expect(
        equals(res, multiplied),
        "multiplies correct"
    );
}

int testDivision() {
    struct Tuple tuple = createTuple(1, -2, 3, -4);
    struct Tuple divided = divide(tuple, 2);
    struct Tuple res = createTuple(0.5, -1, 1.5, -2);
    expect(
        equals(res, divided),
        "divides correct"
    );
}

int testMagnitude() {
    struct Tuple vector1 = createVector(1, 0, 0);
    float mag1 = magnitude(vector1);
    int res1 = 1;
    expect( mag1 == res1, "wrong magnitude mag1" );
    struct Tuple vector2 = createVector(0, 1, 0);
    float mag2 = magnitude(vector2);
    int res2 = 1;
    expect( mag2 == res2, "wrong magnitude mag2" );
    struct Tuple vector3 = createVector(0, 0, 1);
    float mag3 = magnitude(vector3);
    int res3 = 1;
    expect( mag3 == res3, "wrong magnitude mag3" );
    struct Tuple vector4 = createVector(1, 2, 3);
    float mag4 = magnitude(vector4);
    float res4 = sqrt(14);
    expect( mag4 == res4, "wrong magnitude mag4" );
    struct Tuple vector5 = createVector(-1, -2, -3);
    float mag5 = magnitude(vector5);
    float res5 = sqrt(14);
    expect( mag5 == res5, "wrong magnitude mag5" );
}

int testNormalize() {
    struct Tuple vector1 = createVector(4, 0, 0);
    struct Tuple res1 = createVector(1, 0, 0);
    struct Tuple normalized = normalize(vector1);
    expect(equals(normalized, res1), "normalize vector1"); 
    struct Tuple vector2 = createVector(1, 2, 3);
    // struct Tuple res2 = createVector(0.26726, 0.53452, 0.80178);
    struct Tuple res2 = createVector(1/sqrt(14), 2/sqrt(14), 3/sqrt(14));
    struct Tuple normalized2 = normalize(vector2);
    expect(equals(normalized2, res2), "normalize vector2"); 
}

int main() {
    runTestSuit(
        "should create correct tuples\n",
        testTuples
    );
    runTestSuit(
        "should use factories correctly\n",
        testFactories
    );
    runTestSuit(
        "Adding two tuples\n",
        testAddition
    );
    runTestSuit(
        "Subtracting two points\n",
        testSubtraction
    );
    runTestSuit(
        "Negating vectors\n",
        testNegation
    );
    runTestSuit(
        "Multiply tuples\n",
        testMultiply
    );
    runTestSuit(
        "Divide tuples\n",
        testDivision
    );
    runTestSuit(
        "Create Magnitude for vectors\n",
        testMagnitude
    );
    runTestSuit(
        "Create normalized vectors\n",
        testNormalize
    );

    finishTests();
}