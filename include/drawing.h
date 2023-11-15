#ifndef DRAWING_H
#define DRAWING_H

#include "card_vec.h"
#include "ui_tree.h"

#include <SDL2/SDL.h>

void draw_all(const UiNode* root);
void draw_texture(const SDL_Rect* viewport, SDL_Texture* texture);
void draw_colour(const SDL_Rect* viewport, SDL_Colour colour);
void draw_hand(const UiNode* hand);

#endif
