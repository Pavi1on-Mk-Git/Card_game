#ifndef CARD_PARSER_H
#define CARD_PARSER_H

#include "card_vec.h"
#include "error_code.h"

#include <SDL2/SDL.h>
#include <stdio.h>


void parse_card_data(card_entry* card, FILE* card_data, ErrorCode* err);

#endif
