#ifndef CINDER_H
#define CINDER_H
#include <stddef.h>

// ========== GENERAL ===========
#define GREEN "\033[0;32m"
#define RED   "\033[0;31m"
#define WHITE "\033[0;37m"
#define CORRECT_MARK "\u2713"
#define INCORRECT_MARK "\u2717"


// ========== RUNNER ============
#define FUNC_BUFF 100
typedef void (*cinder_test_fn)(void);

struct cinder_test {
    cinder_test_fn test;
    char *function_name;
    char *msg;
    int checks;
    int passed;
};


// ========== FUNCTIONS ==========
void report_result(int result, char *expr, char *file, int line);
void register_test(struct cinder_test *test);


// ========== MACROS =========
#define CHECK(expr) report_result(expr, #expr, __FILE__, __LINE__)

#define CINDER_NAME(Function, Suffix)                                   \
    Function ## _ ## Suffix

#define CINDER_PROTOTYPE(Function)                                      \
    void CINDER_NAME(Function, fn)(void)

#define TEST(Function, Message)                                         \
    CINDER_PROTOTYPE(Function);                                         \
    struct cinder_test CINDER_NAME(Function, meta) = {                  \
        CINDER_NAME(Function, fn),                                      \
        #Function,                                                      \
        Message,                                                        \
        0,                                                              \
        0                                                               \
    };                                                                  \
    __attribute__((constructor))                                        \
    static void CINDER_NAME(Function, reg)(void) {                      \
        register_test(&CINDER_NAME(Function, meta));                    \
    }                                                                   \
    CINDER_PROTOTYPE(Function)              



// ========== GLOBAL =========
extern struct cinder_test **testing_list;
extern struct cinder_test *current_test;


#endif
