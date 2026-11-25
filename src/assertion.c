#include <stdio.h>
#include "cinder.h"


static void record_result(int passed, enum cinder_severity sev) {
    // Update the current test stats
    current_test->checks++;
    current_test->passed += passed;

    if (!passed && sev == CINDER_FATAL) {
        cinder_finish_test();
    }
}


void report_result(int result, char *expr, char *file, int line, enum cinder_severity sev) {
    if (result) {
        printf("  %s%s %s\n%s", GREEN, CORRECT_MARK, expr, RESET);
    } 
    else {
        printf("  %s%s FAILED: %s\n%s:%d\nCHECK failed: %s\n\n%s",
            RED, INCORRECT_MARK, current_test->msg, file, line, expr, RESET);
    }
    record_result(result, sev);
}


void report_eq(long long actual, long long expected, char *actual_str, char *expected_str, 
               char *file, int line, enum cinder_severity sev) {
    if (actual == expected) {
        printf("  %s%s PASSED: %s\n%s", GREEN, CORRECT_MARK, current_test->msg, RESET);
    }
    else {
        // Print the expected and the actual
        const char *name = (sev == CINDER_FATAL) ? "REQUIRE_EQ" : "CHECK_EQ";
        printf("  %s%s %s(%s, %s)   %s:%d\n"
               "    expected:   %lld\n"
               "    actual  :   %lld%s\n",
               RED, INCORRECT_MARK, name, actual_str, expected_str,
               file, line, expected, actual, RESET
        );
    }
    record_result((actual == expected), sev);
}


