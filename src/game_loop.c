#include "game_loop.h"

#include <math.h>

ErrorCode initialize_SDL(SDL_Window** window, SDL_Renderer** renderer)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL Initialization failed: %s\n", SDL_GetError());
        return ERR_INIT;
    }

    *window = SDL_CreateWindow(
        "Card game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS
    );

    if(window == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Window creation failed: %s\n", SDL_GetError());
        return ERR_INIT;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Renderer creation failed: %s\n", SDL_GetError());
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
        puts(error_msg);
        return;
    }

    SDL_RenderSetViewport(window_state->renderer, &GAME_VIEWPORT);

    card* cards = {0};

    if(load_card_data(&cards, window_state->renderer) != ERR_OK)
    {
        puts(error_msg);
        return;
    }

    card* curr_card = cards;

    while(!window_state->quit)
    {
        window_state->frame_start = SDL_GetTicks64();

        while(SDL_PollEvent(&window_state->event))
        {
            handle_bar(window_state);
        }

        if(!window_state->is_fullscreen)
            draw_bar(window_state->renderer, bar);

        SDL_Rect card_rect;

        SDL_RenderFillRect(window_state->renderer, NULL);

        SDL_QueryTexture((SDL_Texture*) curr_card->data->texture, NULL, NULL, &card_rect.w, &card_rect.h);

        card_rect.w = card_rect.w / 2;
        card_rect.h = card_rect.h / 2;
        card_rect.x = GAME_VIEWPORT.w / 2 - card_rect.w / 2;
        card_rect.y = GAME_VIEWPORT.h / 2 - card_rect.h / 2;

        SDL_RenderCopyEx(
            window_state->renderer, (SDL_Texture*) curr_card->data->texture, NULL, &card_rect, angle, NULL,
            SDL_FLIP_NONE
        );

        SDL_RenderPresent(window_state->renderer);

        if((++counter % FPS) == 0)
            if((curr_card = curr_card->next) == NULL)
                curr_card = cards;

        angle = fmod(angle + (30.0 / FPS), 360.0);

        delay(window_state);
    }

    free_cards(&cards);
    SDL_DestroyTexture(bar);
}
