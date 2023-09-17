#ifndef DRAWING_H
#define DRAWING_H

#include "card_parser.h"
#include "error_code.h"
#include "types.h"


ErrorCode load_texture(SDL_Texture** texture, SDL_Renderer* renderer, const char* path);
ErrorCode load_card_data(card** head, SDL_Renderer* renderer);
void draw_bar(SDL_Renderer* renderer, SDL_Texture* bar);

#endif
