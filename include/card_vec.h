#ifndef CARD_VEC_H
#define CARD_VEC_H

#include "constants.h"
#include "error_code.h"

#include <SDL2/SDL.h>

#define CARD_WIDTH 64
#define CARD_HEIGHT 89

typedef struct card_entry
{
    char name[MAX_NAME_LEN + 1];
    SDL_Texture* texture;
    SDL_Rect cutout_rect;
} card_entry;

typedef struct card_vec
{
    card_entry** data;
    size_t size, capacity;
} card_vec;

extern card_vec cards;

void push_back(card_vec* vec, card_entry* new_card);
int compare_cards(void* context, const void* first, const void* second);
void sort_vec(card_vec* vec);
void free_cards(card_vec* vec);
SDL_bool check_duplicate(const card_vec* vec, const card_entry* new_card);

#endif
