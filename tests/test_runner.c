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

// Example Test
void sum_test(void) {
    int c = sum(4, 5);
    CHECK(c == 9);
    // (c == 9) ? printf("Correct!\n") : printf("Incorrect!\n");
}

void difference_test(void) {
    int c = difference(11, 6);
    (c == 5) ? printf("Correct!\n") : printf("Incorrect!\n");
}
