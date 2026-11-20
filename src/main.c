#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cinder.h"

void sum_test(void);

int main(void) {
    FuncRegister *reg = init_reg();
    register_function(reg, &sum_test);
    reg_run(reg);

    // CinderTestFn tests[] = {sum_test};
    // run_function(tests, 1);

    return 0;
}
