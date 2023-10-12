#ifndef HELPERS_H
#define HELPERS_H

#include "player_state.h"

#include <SDL2/SDL.h>

#define RECT(frect) ((SDL_Rect){.x = (int) (frect).x, .y = (int) (frect).y, .w = (int) (frect).w, .h = (int) (frect).h})

void get_logical_mouse(float* x, float* y);
SDL_bool mouse_in_rotated_rect(const SDL_FRect* dest_rect, const SDL_FPoint* rot_center, const double angle);

#endif
