#ifndef WINDOW_STATE_H
#define WINDOW_STATE_H

#include "ui_tree.h"

#include <SDL2/SDL.h>

typedef struct WindowState
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_bool quit : 1, dragging : 1, want_exit : 1, want_fullscreen : 1, want_min : 1, is_fullscreen : 1;
    SDL_Point mouse_offset;
    SDL_Event event;
    Uint64 frame_start, frame_time;
    UiNode* ui_tree;
} WindowState;

extern WindowState window_state;

#endif
