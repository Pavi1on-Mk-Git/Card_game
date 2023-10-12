#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include "card_vec.h"

#include <SDL2/SDL.h>

#define MAX_HAND_SIZE 10

typedef struct RotationData
{
    SDL_FRect dest_rect;
    SDL_FPoint rot_center;
    double angles[MAX_HAND_SIZE];
} RotationData;

typedef struct PlayerState
{
    SDL_bool card_grab_bitmap[MAX_HAND_SIZE];
    RotationData rotation_data;
    card_vec hand;
} PlayerState;

extern PlayerState player_state;

void init_player_state();

#endif
