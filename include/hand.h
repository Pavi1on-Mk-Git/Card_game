#ifndef HAND_H
#define HAND_H

#include "card_vec.h"

#include <SDL2/SDL.h>

#define MAX_HAND_SIZE 10

typedef struct
{
    SDL_FRect dest_rect;
    SDL_FPoint rot_center;
    double angles[MAX_HAND_SIZE];
    SDL_bool card_grab_bitmap[MAX_HAND_SIZE];
} HandMetadata;

typedef struct
{
    card_entry* cards[MAX_HAND_SIZE];
    unsigned char curr_size;
    HandMetadata metadata;
} Hand;

#endif
