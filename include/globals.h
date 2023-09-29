#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL2/SDL.h>

#define UNUSED(x) (void) (x)

#define SCREEN_WIDTH 1280
#define BASE_SCREEN_HEIGHT 720
#define BAR_HEIGHT 34
#define BUTTON_WIDTH ((3 * BAR_HEIGHT) / 2)
#define BUTTON_BORDER 3
#define SCREEN_HEIGHT (BASE_SCREEN_HEIGHT + BAR_HEIGHT)
#define FPS 120
#define MAX_NAME_LEN 64
#define GAME_VIEWPORT_COUNT 1

#define FRAME_TIME 1000.0 / FPS

#define BAR_VIEWPORT                                       \
    (SDL_Rect)                                             \
    {                                                      \
        .x = 0, .y = 0, .w = SCREEN_WIDTH, .h = BAR_HEIGHT \
    }
#define EXIT_BUTTON                                                                                                  \
    (SDL_Rect)                                                                                                       \
    {                                                                                                                \
        .x = SCREEN_WIDTH - BUTTON_WIDTH + BUTTON_BORDER, .y = BUTTON_BORDER, .w = BUTTON_WIDTH - 2 * BUTTON_BORDER, \
        .h = BAR_HEIGHT - 2 * BUTTON_BORDER                                                                          \
    }
#define FULLSCREEN_BUTTON                                                                                             \
    (SDL_Rect)                                                                                                        \
    {                                                                                                                 \
        .x = EXIT_BUTTON.x - BUTTON_WIDTH + BUTTON_BORDER, .y = BUTTON_BORDER, .w = BUTTON_WIDTH - 2 * BUTTON_BORDER, \
        .h = BAR_HEIGHT - 2 * BUTTON_BORDER                                                                           \
    }
#define MIN_BUTTON                                                                   \
    (SDL_Rect)                                                                       \
    {                                                                                \
        .x = FULLSCREEN_BUTTON.x - BUTTON_WIDTH + BUTTON_BORDER, .y = BUTTON_BORDER, \
        .w = BUTTON_WIDTH - 2 * BUTTON_BORDER, .h = BAR_HEIGHT - 2 * BUTTON_BORDER   \
    }

extern SDL_Rect game_viewports[GAME_VIEWPORT_COUNT];

#define GAME_VIEWPORT game_viewports[0]

void setup_viewports();

typedef struct WindowState
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_bool quit : 1, dragging : 1, want_exit : 1, want_fullscreen : 1, want_min : 1, is_fullscreen : 1;
    SDL_Point mouse_offset;
    SDL_Event event;
    Uint64 frame_start, frame_time;
} WindowState;

#endif
