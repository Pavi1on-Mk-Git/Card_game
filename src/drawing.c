#include "drawing.h"

#include "helpers.h"
#include "player_state.h"
#include "textures.h"
#include "viewports.h"

#include <math.h>

void draw_bar()
{
    SDL_RenderSetViewport(window_state.renderer, &RECT(BAR_VIEWPORT));

    SDL_RenderCopy(window_state.renderer, BAR.texture, NULL, NULL);
}

void draw_draw_button()
{
    SDL_RenderSetViewport(window_state.renderer, &RECT(DRAW_BUTTON_VIEWPORT));

    SDL_RenderCopy(window_state.renderer, DRAW_BUTTON.texture, NULL, NULL);
}

double rotation(double card_index, double hand_size)
{
    return 4 * hand_size * ((card_index - (hand_size) / 2 + 0.5) / hand_size);
}

void draw_hand_viewport()
{
    double angle;

    SDL_RenderSetViewport(window_state.renderer, &RECT(HAND_VIEWPORT));

    for(unsigned i = 0; i < player_state.hand.curr_size; i++)
    {
        angle = rotation(i, player_state.hand.curr_size);

        player_state.hand.metadata.angles[i] = angle;

        if(player_state.hand.metadata.card_grab_bitmap[i] == SDL_FALSE)
            SDL_RenderCopyExF(
                window_state.renderer, player_state.hand.cards[i]->texture, &player_state.hand.cards[i]->cutout_rect,
                &player_state.hand.metadata.dest_rect, angle, &player_state.hand.metadata.rot_center, SDL_FLIP_NONE
            );
    }
}

void draw_game_viewport()
{
    SDL_RenderSetViewport(window_state.renderer, &RECT(GAME_VIEWPORT));
    SDL_SetRenderDrawColor(window_state.renderer, 0x78, 0x20, 0x1c, 0xff);
    SDL_RenderFillRect(window_state.renderer, NULL); // Clear the game viewport

    draw_hand_viewport();
}

void draw_right_bar_viewport()
{
    SDL_RenderSetViewport(window_state.renderer, &RECT(RIGHT_BAR_VIEWPORT));
    SDL_SetRenderDrawColor(window_state.renderer, 0xc0, 0xc0, 0xc0, 0xff);
    SDL_RenderFillRect(window_state.renderer, NULL); // Clear the right button viewport

    DRAW_BUTTON.draw();
}
