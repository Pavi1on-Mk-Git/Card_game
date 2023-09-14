#ifndef DRAWING_H
#define DRAWING_H

#include "types.h"
#include "card_parser.h"
#include "error_code.h"

ErrorCode load_card(SDL_Texture** texture, SDL_Renderer* renderer, const char* path);
ErrorCode load_cards(card** head, SDL_Renderer* renderer);

#endif
