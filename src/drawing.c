#include "drawing.h"

#include "helpers.h"
#include "player_state.h"
#include "viewports.h"

#include <math.h>


void draw_bar(SDL_Renderer* renderer, SDL_Texture* bar)
{
    SDL_RenderSetViewport(renderer, &RECT(BAR_VIEWPORT));

    SDL_RenderCopy(renderer, bar, NULL, NULL);
}

double rotation(double card_index, double hand_size)
{
    return 6 * hand_size * ((card_index - (hand_size) / 2 + 0.5) / hand_size);
}

void draw_hand(SDL_Renderer* renderer, const card_vec* hand)
{
    SDL_FRect dest_rect;
    double angle;
    SDL_FPoint rot_center;

    SDL_Rect curr_viewport;
    SDL_RenderGetViewport(renderer, &curr_viewport);

    for(unsigned i = 0; i < hand->size; i++)
    {
        dest_rect = (SDL_FRect
        ){.x = (curr_viewport.w - CARD_WIDTH) / 2,
          .y = (curr_viewport.h - CARD_HEIGHT) / 2,
          .w = 2 * CARD_WIDTH,
          .h = 2 * CARD_HEIGHT};

        rot_center = (SDL_FPoint){.x = dest_rect.w / 2, .y = dest_rect.h * 6};

        angle = rotation(i, hand->size);

        SDL_RenderCopyExF(
            renderer, hand->data[i]->texture, &hand->data[i]->cutout_rect, &dest_rect, angle, &rot_center, SDL_FLIP_NONE
        );
    }
}

void draw_draw_button(SDL_Renderer* renderer, SDL_Texture* button)
{
    SDL_RenderSetViewport(renderer, &RECT(DRAW_BUTTON));

    SDL_RenderCopy(renderer, button, NULL, NULL);
}

void draw_game_viewport(SDL_Renderer* renderer)
{
    SDL_RenderSetViewport(renderer, &RECT(GAME_VIEWPORT));
    SDL_SetRenderDrawColor(renderer, 0x78, 0x20, 0x1c, 0xff);
    SDL_RenderFillRect(renderer, NULL); // Clear the game viewport

    draw_hand(renderer, &player_state.hand);
}

void draw_right_bar_viewport(SDL_Renderer* renderer, SDL_Texture* button)
{
    SDL_RenderSetViewport(renderer, &RECT(RIGHT_BAR_VIEWPORT));
    SDL_SetRenderDrawColor(renderer, 0xc0, 0xc0, 0xc0, 0xff);
    SDL_RenderFillRect(renderer, NULL); // Clear the right button viewport

    draw_draw_button(renderer, button);
}
