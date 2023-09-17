#include "event_handlers.h"

void handle_bar(WindowState* window_state)
{
    switch(window_state->event.type)
    {
    case SDL_MOUSEBUTTONDOWN:

        if(window_state->event.button.button == SDL_BUTTON_LEFT)
        {
            SDL_Point mouse;
            SDL_GetMouseState(&mouse.x, &mouse.y);

            if(SDL_PointInRect(&mouse, &EXIT_BUTTON))
            {
                window_state->want_exit = SDL_TRUE;
            }
            else if(SDL_PointInRect(&mouse, &FULLSCREEN_BUTTON))
            {
                window_state->want_fullscreen = SDL_TRUE;
            }
            else if(SDL_PointInRect(&mouse, &MIN_BUTTON))
            {
                window_state->want_min = SDL_TRUE;
            }
            else if(SDL_PointInRect(&mouse, &BAR_VIEWPORT))
            {
                SDL_GetGlobalMouseState(&mouse.x, &mouse.y);
                SDL_GetWindowPosition(
                    window_state->window, &window_state->mouse_offset.x, &window_state->mouse_offset.y
                );
                window_state->mouse_offset.x -= mouse.x;
                window_state->mouse_offset.y -= mouse.y;
                window_state->dragging = SDL_TRUE;
            }
        }
        break;

    case SDL_MOUSEMOTION:

        if(window_state->dragging)
        {
            SDL_Point mouse;
            SDL_GetGlobalMouseState(&mouse.x, &mouse.y);
            SDL_SetWindowPosition(
                window_state->window, mouse.x + window_state->mouse_offset.x, mouse.y + window_state->mouse_offset.y
            );
        }
        break;

    case SDL_MOUSEBUTTONUP:

        if(window_state->event.button.button == SDL_BUTTON_LEFT)
        {
            window_state->dragging = SDL_FALSE;

            SDL_Point mouse;
            SDL_GetMouseState(&mouse.x, &mouse.y);
            if(window_state->want_exit && SDL_PointInRect(&mouse, &EXIT_BUTTON))
            {
                window_state->quit = SDL_TRUE;
            }
            else if(window_state->want_fullscreen && SDL_PointInRect(&mouse, &FULLSCREEN_BUTTON))
            {
                SDL_SetWindowFullscreen(window_state->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                SDL_RenderSetLogicalSize(window_state->renderer, SCREEN_WIDTH, BASE_SCREEN_HEIGHT);
                window_state->want_fullscreen = SDL_FALSE;
                window_state->is_fullscreen = SDL_TRUE;
            }
            else if(window_state->want_min && SDL_PointInRect(&mouse, &MIN_BUTTON))
            {
                SDL_MinimizeWindow(window_state->window);
                window_state->want_min = SDL_FALSE;
            }
        }
        break;

    case SDL_KEYUP:

        if(window_state->is_fullscreen && window_state->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
        {
            SDL_SetWindowFullscreen(window_state->window, 0);
            window_state->is_fullscreen = SDL_FALSE;
        }
        break;
    }
}
