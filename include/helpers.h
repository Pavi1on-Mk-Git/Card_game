#ifndef HELPERS_H
#define HELPERS_H

#include <stdio.h>
#include "globals.h"
#include "error_code.h"

ErrorCode read_until(FILE* file, char* buffer, char end_char, int offset);

#endif