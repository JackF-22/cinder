#include <stdio.h>
#include "cinder.h"

// Function that runs other functions
void run_function(CinderTestFn *func) {
    CinderTestFn current = *func;
    while (current != NULL) {
        current();
        current = *(current + 1);
    }
    return;
}
