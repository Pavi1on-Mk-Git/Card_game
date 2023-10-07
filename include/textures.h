#ifndef TEXTURES_H
#define TEXTURES_H

#include "card_vec.h"
#include "error_code.h"
#include "loading.h"
#include "window_state.h"

#include <SDL2/SDL.h>

extern SDL_Texture *bar, *button;
extern card_vec cards;

ErrorCode load_all_textures();
void free_all_textures();

#endif
