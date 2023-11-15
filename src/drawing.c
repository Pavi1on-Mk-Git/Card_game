#include "drawing.h"

#include "helpers.h"
#include "player_state.h"
#include "viewports.h"
#include "window_state.h"

#include <math.h>

void draw_all(const UiNode* root)
{
    if(!root)
        return;

    if(root->state.hidden)
        return;

    switch(root->draw_type)
    {
    case TEXTURE:
        draw_texture(&RECT(root->viewport), root->texture);
        break;
    case COLOUR:
        draw_colour(&RECT(root->viewport), root->colour);
        break;
    case OTHER:
        root->draw(root);
    case NONE:
        break;
    }

    for(int i = 0; i < root->children_size; i++)
        draw_all(&root->children[i]);
}

void draw_texture(const SDL_Rect* viewport, SDL_Texture* texture)
{
    SDL_RenderSetViewport(window_state.renderer, viewport);
    SDL_RenderCopy(window_state.renderer, texture, NULL, NULL);
}

void draw_colour(const SDL_Rect* viewport, SDL_Colour colour)
{
    SDL_RenderSetViewport(window_state.renderer, viewport);
    SDL_SetRenderDrawColor(window_state.renderer, colour.r, colour.g, colour.b, colour.a);
    SDL_RenderFillRect(window_state.renderer, NULL);
}

double rotation(double card_index, double hand_size)
{
    return 4 * hand_size * ((card_index - (hand_size) / 2 + 0.5) / hand_size);
}

void draw_hand(const UiNode* hand)
{
    double angle;

    SDL_RenderSetViewport(window_state.renderer, &RECT(hand->viewport));

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
