#ifndef DRAWING_H
#define DRAWING_H

#include "card_vec.h"

#include <SDL2/SDL.h>


void draw_bar(SDL_Renderer* renderer, SDL_Texture* bar);
void draw_hand(SDL_Renderer* renderer, const card_vec* hand);
void draw_draw_button(SDL_Renderer* renderer, SDL_Texture* button);

void draw_game_viewport(SDL_Renderer* renderer);
void draw_right_bar_viewport(SDL_Renderer* renderer, SDL_Texture* button);

#endif
