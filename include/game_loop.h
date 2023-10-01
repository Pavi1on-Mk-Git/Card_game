#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include "error_code.h"

#include <SDL2/SDL.h>

ErrorCode initialize_SDL(SDL_Window** window, SDL_Renderer** renderer);
void delay();
void game_loop();

#endif
