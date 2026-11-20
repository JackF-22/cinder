#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cinder.h"

void sum_test(void);
void difference_test(void);

int main(void) {
    FuncRegister *reg = init_reg();
    CinderTest *test = init_test(sum_test);

    register_test(reg, *test);
    // register_function(reg, &difference_test);
    
    reg_run(reg);

    // Clean up memory
    free_register(reg);

    return 0;
}
