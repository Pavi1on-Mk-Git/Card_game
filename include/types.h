#ifndef TYPES_H
#define TYPES_H

#include "error_code.h"
#include "globals.h"


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
    card_entry* data;
    size_t size, capacity;
} card_vec;

void add(card_vec* head, card_entry* new_card);
void free_cards(card_vec* head);
ErrorCode check_duplicate(card_vec* head, card_entry* new_card);

#endif
