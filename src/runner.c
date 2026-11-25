#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "cinder.h"
#include <signal.h>

struct cinder_test **testing_list = NULL;
struct cinder_test *current_test = NULL;
static int num_tests = 0;
static int test_cap  = FUNC_BUFF;

// Public file descriptors
static int test_fd[2];


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
 * Finish the function such that we write to the proper file descriptor
 */
void cinder_finish_test(void) {
    if(write(test_fd[1], &current_test->passed, sizeof(int)) != sizeof(int) ||
       write(test_fd[1], &current_test->checks, sizeof(int)) != sizeof(int)) {
        printf("Incorrect size passed\n");
        exit(EXIT_FAILURE);
    }

    close(test_fd[1]);
    exit(EXIT_SUCCESS);
}


/**
 * Move through the testing_list and run the test functions
 */
int run_functions(void) {
    int n_pass = 0;
    int n_fail = 0;
    int n_crash = 0;

    for (int i = 0; i < num_tests; i++) {
        current_test = *(testing_list + i);
        cinder_test_fn f = current_test->test;

        // Print general test information:
        // printf("\n========= %s: %s =========\n", current_test->suite, current_test->name);
        printf("\n%s %s/%s  %s\n", CINDER_MARK_TEST, current_test->suite,
                                    current_test->name, current_test->msg);    

        // Fork the process, create a child
        // int fd[2];
        if (pipe(test_fd) == -1) {
            n_crash++;
            perror("Piping error");
            exit(EXIT_FAILURE);
        }

        fflush(stdout);
        pid_t pid = fork();

        if (pid == 0) {
            // Child process, run our function
            close(test_fd[0]);  // Close the reading end
            
            // Run the function and get final counts to the parent
            alarm(CINDER_TIMEOUT);
            f();

            // Call the function to write outputs
            cinder_finish_test();
        }
        else if (pid > 0) {
            // Wait for child to send a string
            int status;
            waitpid(pid, &status, 0);
            close(test_fd[1]);

            if (WIFEXITED(status)) {
                // the child called exit() or returned normally
                int code = WEXITSTATUS(status);   // the number it passed to exit()

                if (code != 0) {
                    printf("Error: Exited with code %d\n", code);
                    n_crash++;
                }
                else {
                    int child_checks = 0;
                    int child_passed = 0;

                    // Error handling the reads
                    if (read(test_fd[0], &child_passed, sizeof(int)) != sizeof(int) ||
                        read(test_fd[0], &child_checks, sizeof(int)) != sizeof(int)) {
                        printf("Read error\n");
                        n_crash++;
                    }
                    else {
                        n_pass++;
                        printf("  PASS: %d/%d\n", child_passed, child_checks);
                    }

                    if (child_passed != child_checks) {
                        n_fail++;
                    }
                }
            }
            else if (WIFSIGNALED(status)) {
                // a signal killed the child
                int sig = WTERMSIG(status);       // e.g. SIGSEGV = 11
                if (sig == SIGALRM) {
                    printf("  %sTIMED OUT (5s)\n%s", RED, RESET);
                    n_crash++;
                }
                else {
                    printf("  %sCRASHED: %s\n%s", RED, strsignal(sig), RESET);
                    n_crash++;
                }
            }

            close(test_fd[0]);
        }
        else {
            n_crash++;
            perror("Forking error");
            close(test_fd[0]);
            close(test_fd[1]);
            exit(EXIT_FAILURE);
        }
    }
    printf("\n");
    for (int i = 0; i < 50; i++) {
        fputs(CINDER_RULE_CHAR, stdout);
    }
    printf("\n");

    // Print out final stats
    int total_tests = n_pass + n_fail + n_crash;
    printf("%d tests %s %d passed %s %d failed %s %d crashed\n",
            total_tests, CINDER_SEP, n_pass, CINDER_SEP, n_fail, CINDER_SEP, n_crash);
    printf("\n");
    
    return n_fail + n_crash == 0;
}


int main(void) {
    int correct = run_functions();
    return correct ? 0 : EXIT_FAILURE;
}

