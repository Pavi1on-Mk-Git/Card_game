#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include "drawing.h"
#include "error_code.h"

ErrorCode initialize_SDL(SDL_Window* window[static 1], SDL_Renderer* renderer[static 1]);
void game_loop(SDL_Renderer* renderer);

#endif
