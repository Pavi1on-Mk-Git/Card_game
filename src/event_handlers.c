#include "event_handlers.h"

#include "helpers.h"
#include "player_state.h"
#include "viewports.h"
#include "window_state.h"

void handle_bar()
{
    switch(window_state.event.type)
    {
    case SDL_MOUSEBUTTONDOWN:

        if(window_state.event.button.button == SDL_BUTTON_LEFT)
        {
            SDL_FPoint mouse;

            get_logical_mouse(window_state.renderer, &mouse.x, &mouse.y);

            if(SDL_PointInFRect(&mouse, &EXIT_BUTTON))
            {
                window_state.want_exit = SDL_TRUE;
            }
            else if(SDL_PointInFRect(&mouse, &FULLSCREEN_BUTTON))
            {
                window_state.want_fullscreen = SDL_TRUE;
            }
            else if(SDL_PointInFRect(&mouse, &MIN_BUTTON))
            {
                window_state.want_min = SDL_TRUE;
            }
            else if(SDL_PointInFRect(&mouse, &BAR_VIEWPORT))
            {
                SDL_Point real_mouse;

                SDL_GetGlobalMouseState(&real_mouse.x, &real_mouse.y);
                SDL_GetWindowPosition(window_state.window, &window_state.mouse_offset.x, &window_state.mouse_offset.y);
                window_state.mouse_offset.x -= real_mouse.x;
                window_state.mouse_offset.y -= real_mouse.y;
                window_state.dragging = SDL_TRUE;
            }
        }
        break;

    case SDL_MOUSEMOTION:

        if(window_state.dragging)
        {
            SDL_Point real_mouse;
            SDL_GetGlobalMouseState(&real_mouse.x, &real_mouse.y);
            SDL_SetWindowPosition(
                window_state.window, real_mouse.x + window_state.mouse_offset.x,
                real_mouse.y + window_state.mouse_offset.y
            );
        }
        break;

    case SDL_MOUSEBUTTONUP:

        if(window_state.event.button.button == SDL_BUTTON_LEFT)
        {
            window_state.dragging = SDL_FALSE;

            SDL_FPoint mouse;

            get_logical_mouse(window_state.renderer, &mouse.x, &mouse.y);

            if(window_state.want_exit && SDL_PointInFRect(&mouse, &EXIT_BUTTON))
            {
                window_state.quit = SDL_TRUE;
            }
            else if(window_state.want_fullscreen && SDL_PointInFRect(&mouse, &FULLSCREEN_BUTTON))
            {
                SDL_SetWindowFullscreen(window_state.window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                SDL_RenderSetLogicalSize(window_state.renderer, SCREEN_WIDTH, BASE_SCREEN_HEIGHT);
                window_state.want_fullscreen = SDL_FALSE;
                window_state.is_fullscreen = SDL_TRUE;
                for(unsigned i = 0; i < GAME_VIEWPORT_COUNT; i++)
                    game_viewports[i].y -= BAR_HEIGHT;
            }
            else if(window_state.want_min && SDL_PointInFRect(&mouse, &MIN_BUTTON))
            {
                SDL_MinimizeWindow(window_state.window);
                window_state.want_min = SDL_FALSE;
            }
        }
        break;
    }
}

void handle_esc()
{
    switch(window_state.event.type)
    {
    case SDL_KEYUP:

        if(window_state.is_fullscreen && window_state.event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
        {
            SDL_SetWindowFullscreen(window_state.window, 0);
            window_state.is_fullscreen = SDL_FALSE;
            for(unsigned i = 0; i < GAME_VIEWPORT_COUNT; i++)
                game_viewports[i].y += BAR_HEIGHT;
        }
        break;
    }
}

void handle_draw_button(card_vec* cards)
{
    switch(window_state.event.type)
    {
    case SDL_MOUSEBUTTONUP:
        if(window_state.event.button.button == SDL_BUTTON_LEFT)
        {
            SDL_FPoint mouse;

            get_logical_mouse(window_state.renderer, &mouse.x, &mouse.y);

            if(SDL_PointInFRect(&mouse, &DRAW_BUTTON))
            {
                if(player_state.hand.size < 10)
                    push_back(&player_state.hand, cards->data[rand() % cards->size]);
            }
        }
        break;
    }
}
