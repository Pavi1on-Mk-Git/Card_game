#ifndef TYPES_H
#define TYPES_H

#include "globals.h"

typedef struct card_entry
{
    char name[MAX_NAME_LEN];
    void* texture;
} card_entry;

typedef struct card
{
    struct card_entry* data;
    struct card* next;
} card;

void add(card** head, card_entry** new_card);
void free_cards(card** head);

#endif
