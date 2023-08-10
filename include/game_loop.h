#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include "drawing.h"

int initialize_SDL(SDL_Window** window, SDL_Renderer** renderer);
void game_loop(SDL_Renderer* renderer);

#endif
