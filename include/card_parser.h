#ifndef CARD_PARSER_H
#define CARD_PARSER_H

#include <stdio.h>
#include "string.h"
#include "types.h"
#include "drawing.h"
#include "error_code.h"

ErrorCode read_field(FILE card_data[static 1], const char* field_name, char* buffer, const char* buffer_start, const char* buffer_end);
ErrorCode parse_card_data(card_entry** card, FILE card_data[static 1], SDL_Renderer* renderer);

#endif