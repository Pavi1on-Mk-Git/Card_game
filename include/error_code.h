#ifndef ERROR_CODE_H
#define ERROR_CODE_H

#include "globals.h"

typedef enum ErrorCode
{
    ERR_OK,
    ERR_INIT,
    ERR_FILE_FORMAT,
    ERR_MAX_LEN,
    ERR_SDL
} ErrorCode;

extern char error_msg[MAX_NAME_LEN];

#endif
