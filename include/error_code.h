#ifndef ERROR_CODE_H
#define ERROR_CODE_H

#include "constants.h"

typedef enum ErrorCode
{
    ERR_OK,
    ERR_INIT,
    ERR_FILE_FORMAT,
    ERR_SDL,
    ERR_CARD_DUP,
    ERR_NULL,
    ERR_TEXTURE,
    ERR_MEM,
}

ErrorCode;

extern char* error_msg;

#endif
