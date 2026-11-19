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
void sum_test() {
    int c = sum(4, 5);
    (c == 9) ? printf("Correct!\n") : printf("Incorrect!\n");
    return;
}

int main(void) {
    run_function(sum_test);
    return 0;
}