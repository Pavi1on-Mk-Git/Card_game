#include "helpers.h"

void get_logical_mouse(SDL_Renderer* renderer, float* x, float* y)
{
    int x1, y1, w1, h1, w2, h2;
    SDL_GetMouseState(&x1, &y1);

    SDL_RenderGetLogicalSize(renderer, &w1, &h1);
    SDL_GetRendererOutputSize(renderer, &w2, &h2);

    if(x)
        *x = ((float) x1) * w1 / w2;
    if(y)
        *y = ((float) y1) * h1 / h2;
}
