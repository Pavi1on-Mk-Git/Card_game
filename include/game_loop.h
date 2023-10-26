#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include "error_code.h"

#include <SDL2/SDL.h>

void initialize_SDL(SDL_Window** window, SDL_Renderer** renderer, ErrorCode* err);
void delay();
void game_loop(ErrorCode* err);

#endif
