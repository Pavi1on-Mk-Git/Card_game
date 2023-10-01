#ifndef HELPERS_H
#define HELPERS_H

#include <SDL2/SDL.h>

#define RECT(frect) ((SDL_Rect){.x = (int) frect.x, .y = (int) frect.y, .w = (int) frect.w, .h = (int) frect.h})

void get_logical_mouse(SDL_Renderer* renderer, float* x, float* y);

#endif
