#include <stdio.h>
#include "cinder.h"

void report_result(int result, char *expr, char *file, int line) {
    // Update the current test stats
    current_test->checks++;

    if (result) {
        printf("%s%s PASSED\n", GREEN, CORRECT_MARK);
        current_test->passed++;
    }
    else {
        printf("%s%s FAILED %s\n%s:%d\nCHECK failed: %s\n",
                RED, INCORRECT_MARK, current_test->msg, file, line, expr);
    }
}
