#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include "drawing.h"
#include "error_code.h"
#include "event_handlers.h"


ErrorCode initialize_SDL(SDL_Window** window, SDL_Renderer** renderer);
void delay(WindowState* window_state);
void game_loop(WindowState* window_state);

#endif
