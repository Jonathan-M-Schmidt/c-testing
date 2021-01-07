#include "../color/color.c"
#include "../test-frame/test-frame.c"

int testColorStructure() {
    Color c = createColor(-0.5, 0.4, 1.7);
    expect(c.red == -0.5f, "color has correct value r");
    expect(c.green == 0.4f, "color has correct value g");
    expect(c.blue == 1.7f, "color has correct value b");
}

int testColorOperations() {
    Color c1 = createColor(0.9, 0.6, 0.75);
    Color c2 = createColor(0.7, 0.1, 0.25);
    Color added = add_c(c1, c2);
    Color res1 = createColor(1.6, 0.7, 1.0);
    expect(equals_c(added, res1), "can add two colors");
    Color subtracted = sub_c(c1, c2);
    Color res2 = createColor(0.2, 0.5, 0.5);
    expect(equals_c(subtracted, res2), "can subtract two colors");
    Color c3 = createColor(0.2, 0.3, 0.4);
    Color res3 = createColor(0.4, 0.6, 0.8);
    Color mulWithScalar = mul_c(c3, 2);
    expect(equals_c(mulWithScalar, res3), "can multiply color with scalar");
    Color c4 = createColor(1, 0.2, 0.4);
    Color c5 = createColor(0.9, 1, 0.1);
    Color hadP = hadamard_product(c4, c5);
    Color res4 = createColor(0.9, 0.2, 0.04);
    expect(equals_c(hadP, res4), "can create correct hadamard product with two colors");
}

int main() {
    runTestSuit(
        "creates correct color structure\n",
        testColorStructure
    );
    runTestSuit(
        "basic operations create correct results\n",
        testColorOperations
    );

    finishTests();
};
