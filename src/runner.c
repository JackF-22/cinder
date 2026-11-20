#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cinder.h"


/**
 * Initialize a function register for testing
 */
FuncRegister *init_reg(void) {
    FuncRegister *reg = malloc(sizeof(FuncRegister));
    reg->num_funcs = 0;
    reg->func_list = malloc(MAXFUNCS * sizeof(CinderTestFn*));
    return reg;
}


/**
 * Add a testing function to the register of functions
 * 
 * @param reg The function register we are adding to
 * @param func The function we are adding to the register
 */
void register_function(FuncRegister *reg, CinderTestFn new_function) {
    reg->func_list[reg->num_funcs] = new_function;
    reg->num_funcs++;
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
        CinderTestFn current = *(reg->func_list + i);
        current();
    }
    return;
}
