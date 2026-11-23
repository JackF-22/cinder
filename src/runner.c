#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cinder.h"

struct cinder_test **testing_list = NULL;
struct cinder_test *current_test = NULL;
static int num_tests = 0;
static int test_cap  = FUNC_BUFF;


/**
 * Add a test to 'testing_list', the list of test structs
 * 
 * @param test The test that we are looking to register
 */
void register_test(struct cinder_test *test) {
    if (testing_list == NULL) {
        // Allocate space for the array of pointers
        testing_list = malloc(FUNC_BUFF * sizeof(struct cinder_test *));
    }
    else if (num_tests >= test_cap) {
        // Reallocate to alter space
        testing_list = realloc(testing_list, (test_cap * 2) * sizeof(struct cinder_test *));
        test_cap *= 2;
    }

    // After these checks, we know we have properly allocated memory
    *(testing_list + num_tests) = test;
    num_tests++;
}


/**
 * Move through the testing_list and run the test functions
 */
void run_functions(void) {
    if (current_test == NULL) {
        current_test = malloc(sizeof(struct cinder_test *));
    }

    for (int i = 0; i < num_tests; i++) {
        current_test = *(testing_list + i);
        cinder_test_fn f = current_test->test;

        // Print general test information:
        printf("\n========= TEST %d =========\n", i+1);
        printf("Function: %s  |  %s\n", current_test->function_name, current_test->msg);
        f();

        // Print testing results:
        printf("%d/%d Tests Passed\n\n", current_test->passed, current_test->checks);
    }
}


/**
 * Free the space created to store the testing functions
 */
void free_functions(void) {
    for (int i = 0; i < num_tests; i++) {
        free(*(testing_list + num_tests));
    }
    free(testing_list);
}


int main(void) {
    run_functions();
    return 0;
}

