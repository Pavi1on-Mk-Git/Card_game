#ifndef EVENT_HANDLERS_H
#define EVENT_HANDLERS_H


#include "card_vec.h"
#include "ui_tree.h"

#include <SDL2/SDL.h>


void handle_all(const UiNode* root);
void handle_top_bar(const UiNode* bar);
void handle_exit_button(const UiNode* exit_button);
void handle_fullscreen_button(const UiNode* fullscreen_button);
void handle_min_button(const UiNode* min_button);
void handle_esc();
void handle_draw_button(const UiNode* draw_button);
void handle_card_grab(const UiNode* hand);

#endif
