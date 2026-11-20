#include <stdio.h>
#include "cinder.h"

void report_result(int result, const char *file, int line) {
    if (result) {
        printf("%s%s PASSED\n", GREEN, CORRECT_MARK);
    }
    else {
        printf("%s%s FAILED | Failure in file: %s on line: %d\n", RED, INCORRECT_MARK, file, line);
    }
}
