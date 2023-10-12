#include "game_loop.h"

#include "drawing.h"
#include "event_handlers.h"
#include "helpers.h"
#include "loading.h"
#include "textures.h"
#include "window_state.h"

#include <math.h>
#include <string.h>

ErrorCode initialize_SDL(SDL_Window** window, SDL_Renderer** renderer)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("SDL Initialization failed: %s\n", SDL_GetError());
        return ERR_INIT;
    }

    *window = SDL_CreateWindow(
        "Card game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS
    );

    if(window == NULL)
    {
        SDL_Log("Window creation failed: %s\n", SDL_GetError());
        return ERR_INIT;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
    {
        SDL_Log("Renderer creation failed: %s\n", SDL_GetError());
        return ERR_INIT;
    }

    SDL_RenderSetLogicalSize(*renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    return ERR_OK;
}

void delay()
{
    window_state.frame_time = SDL_GetTicks64() - window_state.frame_start;

    if(window_state.frame_time < FRAME_TIME)
        SDL_Delay(FRAME_TIME - window_state.frame_time);
}

void game_loop()
{
    if(load_all_interactables() != ERR_OK)
    {
        SDL_Log(error_msg);
        return;
    }

    while(!window_state.quit)
    {
        window_state.frame_start = SDL_GetTicks64();

        while(SDL_PollEvent(&window_state.event))
        {
            if(!window_state.is_fullscreen)
                BAR.handle();

            handle_esc();
            handle_draw_button();
            handle_card_grab();
        }

        if(!window_state.is_fullscreen)
            BAR.draw();

        draw_game_viewport();

        draw_right_bar_viewport();

        SDL_RenderPresent(window_state.renderer);

        delay();
    }
}
