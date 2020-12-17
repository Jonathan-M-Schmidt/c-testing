#include <stdlib.h>
#include <stdbool.h>

static int testSuiteCounter = 1;
static int counter = 0;
static int errors = 0;
static int initErrors = 0;

bool expect(bool condition, char *errorMsg) {
    counter++;
    if(!condition) {
        printf("\tFailing test: %d\n", counter);
        if (errorMsg) {
            printf("\tcustom error message: %s\n", errorMsg);
        }
        errors++;
        return false;
    }
    return true;
}

void initTestSuit(char *testMessage) {
    printf("%d. %s", testSuiteCounter, testMessage);
    initErrors = errors;
    counter = 0;
}

void testSuitResult() {
    if ( initErrors == errors ) {
        printf("\ttestsuit completed without errors: v\n");
    }
    testSuiteCounter++;
}

void runTestSuit(char *testMessage, int (*testFunc)()) {
    initTestSuit(testMessage);
    testFunc();
    testSuitResult();
}

void finishTests() {
    if ( errors > 0){
        printf("\nErrors in testsuit. Errorcount: %d\n", errors);
        exit(EXIT_FAILURE);
    } else {
        printf("\nAll testsuits completed without errors.\n");
        exit(EXIT_SUCCESS);
    }
}