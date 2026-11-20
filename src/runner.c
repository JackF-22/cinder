#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cinder.h"

// Keep track of the current test that is running
CinderTest *current_test = NULL;

/**
 * Create a new test structure
 * 
 * @param func The function that we are basing this structure on
 */
CinderTest *init_test(CinderTestFn func) {
    CinderTest *ct = malloc(sizeof(CinderTest));
    ct->f = func;
    ct->passed = 0;
    return ct;
}


/**
 * Initialize a function register for testing
 */
FuncRegister *init_reg(void) {
    FuncRegister *reg = malloc(sizeof(FuncRegister));
    reg->num_funcs = 0;
    reg->capacity = FUNC_BUFF;
    reg->test_list = malloc(reg->capacity * sizeof(CinderTest));
    return reg;
}


/**
 * Clean up the memory given to a function register
 * 
 * @param reg The register that we are cleaning up
 */
void free_register(FuncRegister *reg) {
    free(reg->test_list);
    free(reg);
}


/**
 * Add a testing function to the register of functions
 * 
 * @param reg The function register we are adding to
 * @param func The function we are adding to the register
 */
void register_test(FuncRegister *reg, CinderTest new_test) {
    if (reg->num_funcs >= reg->capacity) {
        reg->capacity *= 2;
        reg->test_list = (CinderTest*) realloc(reg->test_list, reg->capacity * sizeof(CinderTestFn));
    }
    reg->test_list[reg->num_funcs] = new_test;
    reg->num_funcs++;
    return;
}


/**
 * Run a series of testing functions
 * 
 * @param func Pointer to the start of a list of function pointers
 * @param n The number of functions to run
 */
void run_function(CinderTestFn *func, int n) {
    CinderTestFn current = *func;

    for (int i = 0; i < n; i++) {
        current = *(func + i);
        current();
    }

    return;
}


/**
 * Run a series of testing functions with a dynamic function list
 * 
 * @param reg A struct of tests to run
 */
void reg_run(FuncRegister *reg) {
    for (int i = 0; i < reg->num_funcs; i++) {
        CinderTest test = *(reg->test_list + i);
        CinderTestFn current = test.f;
        current_test = &test;
        current();
        printf("%sTests Passed: %d/%d\n", WHITE, test.passed, test.checks);
    }
    return;
}
