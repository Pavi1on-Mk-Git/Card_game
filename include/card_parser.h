#ifndef CARD_PARSER_H
#define CARD_PARSER_H

#include "error_code.h"
#include "string.h"
#include "texture.h"
#include "types.h"

#include <stdio.h>

ErrorCode parse_card_data(card_entry* card, FILE card_data[static 1], SDL_Renderer* renderer);

#endif
