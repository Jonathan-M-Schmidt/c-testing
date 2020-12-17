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

    finishTests();
}