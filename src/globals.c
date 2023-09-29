#include "globals.h"

SDL_Rect game_viewports[GAME_VIEWPORT_COUNT];

void setup_viewports()
{
    GAME_VIEWPORT = (SDL_Rect){.x = 0, .y = BAR_HEIGHT, .w = SCREEN_WIDTH, .h = BASE_SCREEN_HEIGHT};
}
