#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include "card_vec.h"

typedef struct PlayerState
{
    card_vec hand;
} PlayerState;

extern PlayerState player_state;

#endif
