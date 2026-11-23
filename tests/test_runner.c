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

TEST(negatives, sum, "Two negative numbers") {
    CHECK(-4 + -5 == -9);
}

TEST(bigger_numbers, sum, "Bigger numbers") {
    CHECK(521 + 342 == 863);
}

TEST(crash, null, "Dereferencing NULL") {
    int *p = NULL;
    *p = 1;        // writing to address 0, so the OS sends SIGSEGV
    CHECK(1);      // never reached
}

// Example Test
// void sum_test(void) {
//     CHECK(4 + 8 == 13);
// }

// void difference_test(void) {
//     CHECK(10 - 5 == 5);
// }
