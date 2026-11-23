#include <stdio.h>
#include "cinder.h"

// Example Function
int sum(int a, int b) {
    int add = a + b;
    printf("Sum: %d\n", add);
    return add;
}

int difference(int a, int b) {
    int subtract = a - b;
    printf("Difference: %d\n", subtract);
    return subtract;
}

TEST(sum, negatives, "Two negative numbers") {
    CHECK(-4 + -5 == -9);
}

TEST(sum, bigger_numbers, "Bigger numbers") {
    CHECK(521 + 342 == 863);
}

TEST(null, crash, "Dereferencing NULL") {
    int *p = NULL;
    *p = 1;        // writing to address 0, so the OS sends SIGSEGV
    CHECK(1);      // never reached
}

TEST(hang, forever, "Teset an infinite loop") {
    volatile int x = 1;
    while (x) { };
}

// 1. A failing REQUIRE stops the test
TEST(require, stops, "Fails and halts") {
    REQUIRE(1 == 2);
    printf("SHOULD NOT PRINT\n");
    CHECK(1);
}

// 2. A passing REQUIRE doesn't stop anything
TEST(require, passes, "Passes and continues") {
    REQUIRE(1 == 1);
    CHECK(2 == 2);
}

// 3. Earlier checks still get counted
TEST(require, after_checks, "Counts survive early exit") {
    CHECK(1);        // pass
    CHECK(0);        // fail, but keeps going
    REQUIRE(0);      // fail, stops here
    CHECK(1);        // never runs
}

// 4. Plain CHECK still isn't fatal
TEST(check, continues, "CHECK keeps going") {
    CHECK(0);
    CHECK(1);
}
