#include "player_state.h"

#include "viewports.h"

PlayerState player_state;

void init_player_state()
{
    player_state.hand.metadata.dest_rect = (SDL_FRect
    ){.x = (HAND_VIEWPORT.w - CARD_WIDTH) / 2, .y = 0, .w = CARD_WIDTH, .h = CARD_HEIGHT};

    player_state.hand.metadata.rot_center = (SDL_FPoint
    ){.x = player_state.hand.metadata.dest_rect.w / 2, .y = player_state.hand.metadata.dest_rect.h * 8};
}
