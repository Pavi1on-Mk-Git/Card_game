#include "helpers.h"

#include "viewports.h"
#include "window_state.h"

#include <math.h>

void get_logical_mouse(float* x, float* y)
{
    int x1, y1, w1, h1, w2, h2;
    SDL_GetMouseState(&x1, &y1);

    SDL_RenderGetLogicalSize(window_state.renderer, &w1, &h1);
    SDL_GetRendererOutputSize(window_state.renderer, &w2, &h2);

    if(x)
        *x = ((float) x1) * w1 / w2;
    if(y)
        *y = ((float) y1) * h1 / h2;
}

SDL_bool mouse_in_rotated_rect(const SDL_FRect* dest_rect, const SDL_FPoint* rot_center, const double angle)
{
    int ix, iy;
    float x, y;
    SDL_FPoint mouse;

    SDL_GetMouseState(&ix, &iy);
    SDL_RenderSetViewport(window_state.renderer, &RECT(HAND_VIEWPORT));
    SDL_RenderWindowToLogical(window_state.renderer, ix, iy, &x, &y);

    double s = sin(-M_PI * angle / 180), c = cos(-M_PI * angle / 180);

    mouse.x = (x - rot_center->x) * c - (y - rot_center->y) * s + rot_center->x;
    mouse.y = (x - rot_center->x) * s + (y - rot_center->y) * c + rot_center->y;

    return SDL_PointInFRect(&mouse, dest_rect);
}
