#include "drawing.h"

void draw_bar(SDL_Renderer* renderer, SDL_Texture* bar)
{
    SDL_RenderSetViewport(renderer, &BAR_VIEWPORT);

    SDL_RenderCopy(renderer, bar, NULL, NULL);

    SDL_RenderSetViewport(renderer, &GAME_VIEWPORT);
}
