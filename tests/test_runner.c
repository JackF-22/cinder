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

TEST(sum, "Two negative numbers") {
    CHECK(-4 + -5 == -8);
}

// Example Test
// void sum_test(void) {
//     CHECK(4 + 8 == 13);
// }

// void difference_test(void) {
//     CHECK(10 - 5 == 5);
// }
