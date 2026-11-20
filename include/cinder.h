#ifndef CINDER_H
#define CINDER_H

#include <stddef.h>

// ========== GENERAL ===========
#define GREEN "\033[0;32m"
#define RED   "\033[0;31m"
#define CORRECT_MARK "\u2713"
#define INCORRECT_MARK "\u2717"


// ========== ASSERTION =========
#define CHECK(expr) report_result(expr, __FILE__, __LINE__)

void report_result(int result, const char *file, int line);


// ========== RUNNER ============
#define FUNC_BUFF 100
typedef void (*CinderTestFn)(void);

typedef struct {
    CinderTestFn f;
    int status;
} CinderTest;

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
