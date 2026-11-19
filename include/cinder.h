#ifndef CINDER_H
#define CINDER_H

#include <stddef.h>

typedef void (*CinderTestFn)(void);

void run_function(CinderTestFn *func);



#endif
