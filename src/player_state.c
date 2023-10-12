#include "player_state.h"

#include "viewports.h"

PlayerState player_state;

void init_player_state()
{
    player_state.rotation_data.dest_rect = (SDL_FRect
    ){.x = (HAND_VIEWPORT.w - CARD_WIDTH) / 2, .y = 0, .w = CARD_WIDTH, .h = CARD_HEIGHT};

    player_state.rotation_data.rot_center = (SDL_FPoint
    ){.x = player_state.rotation_data.dest_rect.w / 2, .y = player_state.rotation_data.dest_rect.h * 8};
}
