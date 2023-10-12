#ifndef TEXTURES_H
#define TEXTURES_H

#include "card_vec.h"
#include "error_code.h"
#include "loading.h"
#include "window_state.h"

#include <SDL2/SDL.h>

#define INTER_COUNT 2

typedef struct interactable
{
    SDL_Texture* texture;
    void (*draw)();
    void (*handle)();
} interactable;

extern interactable interactables[INTER_COUNT];

#define BAR interactables[0]
#define DRAW_BUTTON interactables[1]

extern card_vec cards;

ErrorCode load_all_interactables();
void free_all_interactables();

#endif
