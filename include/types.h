#ifndef TYPES_H
#define TYPES_H

#include "error_code.h"
#include "globals.h"


#define CARD_WIDTH 128
#define CARD_HEIGHT 178

typedef struct card_entry
{
    char name[MAX_NAME_LEN];
    SDL_Texture* texture;
    SDL_Rect cutout_rect;
    double scale;
} card_entry;

typedef struct card
{
    struct card_entry* data;
    struct card* next;
} card;

void add(card** head, card_entry** new_card);
void free_cards(card** head);
ErrorCode check_duplicate(card** head, card_entry* new_card);

#endif
