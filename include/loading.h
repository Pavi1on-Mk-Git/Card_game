#ifndef LOADING_H
#define LOADING_H

#include "card_vec.h"
#include "error_code.h"

#include <SDL2/SDL.h>

ErrorCode load_texture(SDL_Texture** texture, SDL_Renderer* renderer, const char* path);
ErrorCode load_card_data(card_vec* head, SDL_Renderer* renderer);

#endif
