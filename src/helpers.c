#include "helpers.h"

ErrorCode read_until(FILE* file, char* buffer, char end_char, int offset)
{
    int curr_char;

    if(offset >= MAX_NAME_LEN)
        return ERR_MAX_LEN;

    int chars_read = offset;

    while((curr_char = fgetc(file)) != (int)end_char)
    {
        if(chars_read >= MAX_NAME_LEN)
            return ERR_MAX_LEN;

        buffer[chars_read] = curr_char;
        chars_read++;
    }

    buffer[chars_read] = '\0';

    return ERR_OK;
}