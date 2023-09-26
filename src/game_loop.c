#include "game_loop.h"

#include "drawing.h"
#include "event_handlers.h"
#include "texture.h"

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

void delay(WindowState* window_state)
{
    window_state->frame_time = SDL_GetTicks64() - window_state->frame_start;

    if(window_state->frame_time < FRAME_TIME)
        SDL_Delay(FRAME_TIME - window_state->frame_time);
}

void game_loop(WindowState* window_state)
{
    double angle = 0;
    int counter = 0;

    SDL_Texture* bar;

    SDL_SetRenderDrawColor(window_state->renderer, 0x78, 0x20, 0x1c, 0xff);

    SDL_RenderSetViewport(window_state->renderer, &BAR_VIEWPORT);

    if(load_texture(&bar, window_state->renderer, "assets/bar.bmp") != ERR_OK)
    {
        strcpy(error_msg, "Couldn't load the bar texture");
        SDL_Log(error_msg);
        return;
    }

    SDL_RenderSetViewport(window_state->renderer, &GAME_VIEWPORT);

    card_vec cards = {0};

    if(load_card_data(&cards, window_state->renderer) != ERR_OK)
    {
        SDL_Log(error_msg);
        free_cards(&cards);
        SDL_DestroyTexture(bar);
        return;
    }

    unsigned curr_card_id = 0;

    while(!window_state->quit)
    {
        window_state->frame_start = SDL_GetTicks64();

        while(SDL_PollEvent(&window_state->event))
        {
            handle_bar(window_state);
        }

        if(!window_state->is_fullscreen)
            draw_bar(window_state->renderer, bar);

        SDL_RenderFillRect(window_state->renderer, NULL);

        SDL_Rect card_rect;

        card_rect.w = 4 * CARD_WIDTH;
        card_rect.h = 4 * CARD_HEIGHT;
        card_rect.x = GAME_VIEWPORT.w / 2 - card_rect.w / 2;
        card_rect.y = GAME_VIEWPORT.h / 2 - card_rect.h / 2;

        SDL_RenderCopyEx(
            window_state->renderer, cards.data[curr_card_id]->texture, &cards.data[curr_card_id]->cutout_rect,
            &card_rect, angle, NULL, SDL_FLIP_NONE
        );

        SDL_RenderPresent(window_state->renderer);

        if((++counter % FPS) == 0)
            if(++curr_card_id == cards.size)
                curr_card_id = 0;

        angle = fmod(angle + (30.0 / FPS), 360.0);

        delay(window_state);
    }

    free_cards(&cards);
    SDL_DestroyTexture(bar);
}
