#ifndef HELPERS_H
#define HELPERS_H

#include "error_code.h"
#include "globals.h"

#include <stdio.h>


ErrorCode read_until(FILE* file, char* buffer, char end_char, int offset);

#endif
