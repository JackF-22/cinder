#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cinder.h"

void sum_test(void);
void difference_test(void);

int main(void) {
    FuncRegister *reg = init_reg();
    TEST(reg, sum_test);
    TEST(reg, difference_test);

    // Run the tests
    reg_run(reg);

    // Clean up memory
    free_register(reg);

    return 0;
}
