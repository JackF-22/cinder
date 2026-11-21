#ifndef CINDER_H
#define CINDER_H

#include <stddef.h>

// ========== GENERAL ===========
#define GREEN "\033[0;32m"
#define RED   "\033[0;31m"
#define WHITE "\033[0;37m"
#define CORRECT_MARK "\u2713"
#define INCORRECT_MARK "\u2717"


// ========== ASSERTION =========
#define TEST(reg, func) handle_test(reg, func, #func)
#define CHECK(expr) report_result(expr, #expr, __FILE__, __LINE__)
void report_result(int result, const char *expr, const char *file, int line);


// ========== RUNNER ============
#define FUNC_BUFF 100
typedef void (*CinderTestFn)(void);

typedef struct {
    CinderTestFn f;
    char *name;
    int checks;
    int passed;
} CinderTest;

// External variable to keep track of current testing function
extern CinderTest *current_test;

typedef struct {
    int num_funcs;
    CinderTest *test_list;
    int capacity;
} FuncRegister;

FuncRegister *init_reg(void);
// CinderTest *init_test(CinderTestFn func);

void handle_test(FuncRegister *reg, CinderTestFn func, char *name);
void free_register(FuncRegister *reg);
void register_test(FuncRegister *reg, CinderTest *test);
void run_function(CinderTestFn *func, int n);
void reg_run(FuncRegister *reg);

#endif
