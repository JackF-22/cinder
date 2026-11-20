#ifndef CINDER_H
#define CINDER_H

#include <stddef.h>

#define MAXFUNCS 1000
typedef void (*CinderTestFn)(void);

typedef struct {
    int num_funcs;
    CinderTestFn *func_list;
} FuncRegister;

FuncRegister *init_reg(void);
void register_function(FuncRegister *reg, CinderTestFn func);
void run_function(CinderTestFn *func, int n);
void reg_run(FuncRegister *reg);

#endif
