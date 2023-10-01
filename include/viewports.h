#ifndef VIEWPORTS_H
#define VIEWPORTS_H

#include "constants.h"

#include <SDL2/SDL.h>

#define BAR_VIEWPORT                                       \
    (SDL_FRect)                                            \
    {                                                      \
        .x = 0, .y = 0, .w = SCREEN_WIDTH, .h = BAR_HEIGHT \
    }
#define EXIT_BUTTON                                                                                                  \
    (SDL_FRect)                                                                                                      \
    {                                                                                                                \
        .x = SCREEN_WIDTH - BUTTON_WIDTH + BUTTON_BORDER, .y = BUTTON_BORDER, .w = BUTTON_WIDTH - 2 * BUTTON_BORDER, \
        .h = BAR_HEIGHT - 2 * BUTTON_BORDER                                                                          \
    }
#define FULLSCREEN_BUTTON                                                                                             \
    (SDL_FRect)                                                                                                       \
    {                                                                                                                 \
        .x = EXIT_BUTTON.x - BUTTON_WIDTH + BUTTON_BORDER, .y = BUTTON_BORDER, .w = BUTTON_WIDTH - 2 * BUTTON_BORDER, \
        .h = BAR_HEIGHT - 2 * BUTTON_BORDER                                                                           \
    }
#define MIN_BUTTON                                                                   \
    (SDL_FRect)                                                                      \
    {                                                                                \
        .x = FULLSCREEN_BUTTON.x - BUTTON_WIDTH + BUTTON_BORDER, .y = BUTTON_BORDER, \
        .w = BUTTON_WIDTH - 2 * BUTTON_BORDER, .h = BAR_HEIGHT - 2 * BUTTON_BORDER   \
    }

#define GAME_VIEWPORT_COUNT 3
extern SDL_FRect game_viewports[GAME_VIEWPORT_COUNT];

#define GAME_VIEWPORT game_viewports[0]
#define RIGHT_BAR_VIEWPORT game_viewports[1]
#define DRAW_BUTTON game_viewports[2]

void setup_viewports();

#endif
