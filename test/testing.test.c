#include <stdlib.h>
#include <stdbool.h>
#include "../tuple/tuple.c"
#include "../test-frame/test-frame.c"

int testFactories() {
    struct Tuple point = createPoint(4, -4, 3);
    struct Tuple tuple = createTuple(4, -4, 3, 1);
    expect(equals(point, tuple), "point should equal tuple");
    struct Tuple vector = createVector(4, -4, 3);
    struct Tuple tuple2 = createTuple(4, -4, 3, 0);
    expect(equals(vector, tuple2), "vector should equal tuple2");
}

int main() {;
    runTestSuit(
        "should trigger a second test file\n",
        testFactories
    );
    
    finishTests();
}