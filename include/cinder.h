#ifndef CINDER_H
#define CINDER_H

#include <stddef.h>

#define FUNC_BUFF 100
typedef void (*CinderTestFn)(void);

typedef struct {
    int num_funcs;
    CinderTestFn *func_list;
    int capacity;
} FuncRegister;

FuncRegister *init_reg(void);
void free_register(FuncRegister *reg);
void register_function(FuncRegister *reg, CinderTestFn func);
void run_function(CinderTestFn *func, int n);
void reg_run(FuncRegister *reg);

#endif
