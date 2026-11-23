#include <stdio.h>
#include "cinder.h"

void report_result(int result, char *expr, char *file, int line, int type) {
    // Update the current test stats
    current_test->checks++;

    if (result) {
        printf("%s%s PASSED: %s\n%s", GREEN, CORRECT_MARK, current_test->msg, RESET);
        current_test->passed++;
    }
    else {
        if (type) {
            cinder_finish_test();
        }
        printf("%s%s FAILED: %s\n%s:%d\nCHECK failed: %s\n%s",
                RED, INCORRECT_MARK, current_test->msg, file, line, expr, RESET);
    }
}
