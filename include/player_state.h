#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include "card_vec.h"
#include "hand.h"

#include <SDL2/SDL.h>

typedef struct PlayerState
{
    Hand hand;
} PlayerState;

extern PlayerState player_state;

void init_player_state();

#endif
