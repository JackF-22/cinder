#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
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
        if (testing_list == NULL) {
            perror("Failed to allocate memory");
            exit(EXIT_FAILURE);
        }
    }
    else if (num_tests >= test_cap) {
        // Reallocate to alter space
        struct cinder_test **tmp = realloc(testing_list, (test_cap * 2) * sizeof(struct cinder_test *));
        if (tmp != NULL) {
            testing_list = tmp;
        }
        else {
            perror("Reallocation failed");
            exit(EXIT_FAILURE);
        }
        test_cap *= 2;
    }

    // After these checks, we know we have properly allocated memory
    *(testing_list + num_tests) = test;
    num_tests++;
}


/**
 * Move through the testing_list and run the test functions
 */
int run_functions(void) {
    int success = 1;
    int fd[2];
    pipe(fd); // Pipe used to send child results to parent

    for (int i = 0; i < num_tests; i++) {
        current_test = *(testing_list + i);
        cinder_test_fn f = current_test->test;

        // Print general test information:
        printf("\n========= TEST: %s =========\n", current_test->function_name);

        // Fork the process, create a child
        fflush(stdout);
        pid_t pid = fork();
        if (pid == 0) {
            // Child process, run our function
            close(fd[0]);  // Close the reading end
            
            // Run the function and get final counts to the parent
            f();
            char output[50];
            snprintf(output, sizeof(output), "%d/%d Checks Passed\n\n", current_test->passed, current_test->checks);

            // Write this to the pipe
            write(fd[1], output, strlen(output) + 1);
            close(fd[1]);

            exit(0);
        }
        else if (pid > 0) {
            // Parent function, get output from child
            char results[100];
            close(fd[1]);   // Close the writing end

            // Read from the child
            read(fd[0], results, 100);
            close(fd[0]);

            printf("Summary: %s\n", results);
        }
        else {
            perror("Forking error");
        }

        if (current_test->passed != current_test->checks) {
            success = 0;
        }
    }
    return success;
}


int main(void) {
    int correct = run_functions();
    return correct ? 0 : EXIT_FAILURE;
}

