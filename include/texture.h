#ifndef TEXTURE_H
#define TEXTURE_H

#include "error_code.h"
#include "globals.h"
#include "types.h"

ErrorCode load_texture(SDL_Texture** texture, SDL_Renderer* renderer, const char* path);
ErrorCode load_card_data(card_vec* head, SDL_Renderer* renderer);

#endif
