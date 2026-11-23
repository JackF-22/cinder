#ifndef CINDER_H
#define CINDER_H
#include <stddef.h>

// ========== GENERAL ===========
#define GREEN "\033[0;32m"
#define RED   "\033[0;31m"
#define RESET "\033[0m"
#define CORRECT_MARK "\u2713"
#define INCORRECT_MARK "\u2717"
#define TIMEOUT 5


// ========== RUNNER ============
#define FUNC_BUFF 100
typedef void (*cinder_test_fn)(void);

static struct cinder_test {
    cinder_test_fn test;
    char *suite;
    char *name;
    char *msg;
    int checks;
    int passed;
};


// ========== FUNCTIONS ==========
void report_result(int result, char *expr, char *file, int line, int type);
void register_test(struct cinder_test *test);
void cinder_finish_test(void);
 

// ========== MACROS =========
#define CHECK(expr) report_result(!!(expr), #expr, __FILE__, __LINE__, 0)
#define REQUIRE(expr) report_result(!!(expr), #expr, __FILE__, __LINE__, 1)

#define CINDER_NAME(Suite, Name, Suffix)                            \
    Suite ## _ ## Name ## _ ## Suffix

#define CINDER_PROTOTYPE(Suite, Name)                               \
    static void CINDER_NAME(Suite, Name, fn)(void)

#define TEST(Suite, Name, Message)                                  \
    CINDER_PROTOTYPE(Suite, Name);                                  \
    struct cinder_test CINDER_NAME(Suite, Name, meta) = {           \
        CINDER_NAME(Suite, Name, fn),                               \
        #Suite,                                                     \
        #Name,                                                      \
        Message,                                                    \
        0,                                                          \
        0                                                           \
    };                                                              \
    __attribute__((constructor))                                    \
    static void CINDER_NAME(Suite, Name, reg)(void) {               \
        register_test(&CINDER_NAME(Suite, Name, meta));             \
    }                                                               \
    CINDER_PROTOTYPE(Suite, Name)              



// ========== GLOBAL =========
extern struct cinder_test **testing_list;
extern struct cinder_test *current_test;


#endif
