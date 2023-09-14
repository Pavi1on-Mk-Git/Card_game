#ifndef CARD_PARSER_H
#define CARD_PARSER_H

#include <stdio.h>
#include "string.h"
#include "types.h"
#include "drawing.h"
#include "error_code.h"

ErrorCode parse_card(card_entry** card, FILE card_data[static 1], SDL_Renderer* renderer);

#endif