#ifndef LOADING_H
#define LOADING_H

#include "card_vec.h"
#include "error_code.h"

#include <SDL2/SDL.h>

SDL_Texture* load_texture(const char* path, ErrorCode* err);
void load_card_data(card_vec* head, ErrorCode* err);

#endif
