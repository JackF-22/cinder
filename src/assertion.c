#include <stdio.h>
#include "cinder.h"

void report_result(int result, const char *file, int line) {
    // Update the current test stats
    current_test->checks++;

    if (result) {
        printf("%s%s PASSED\n", GREEN, CORRECT_MARK);
        current_test->passed++;
    }
    else {
        printf("%s%s FAILED | Failure in file: %s on line: %d\n", RED, INCORRECT_MARK, file, line);
    }
}
