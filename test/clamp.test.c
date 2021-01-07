#include <stdio.h>
#include "../helpers/clamp.c"
#include "../test-frame/test-frame.c"

int testClamp() {
    int a_i = 266;
    int res_i = clamp(a_i, 0, 255);
    expect(res_i == 255, "should clamp int to correct value");
    printf("int result: %i\n", res_i);

    double a_d = 266.0;
    double res_d = clamp(a_d, 0.0, 255.0);
    printf("double result: %f\n", res_d);
    expect(res_d == 255.0, "should clamp double to correct value");

    float a_f = 266.0f;
    float res_f = clamp(a_d, 0.0f, 255.0f);
    printf("float result: %f\n", res_f);
    expect(res_f == 255.0f, "should clamp float to correct value");
};

int main() {
    runTestSuit(
        "clamps values correctly\n",
        testClamp
    );
    finishTests();
}