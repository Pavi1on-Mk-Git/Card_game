#include "types.h"

#include "globals.h"

#include <string.h>

void add(card_vec* head, card_entry* new_card)
{
    if(head->size == head->capacity)
        head->data = realloc(
            head->data, sizeof(card_entry) * (head->capacity ? (head->capacity *= 2) : (head->capacity = 1))
        );

    head->data[head->size++] = new_card;
}

void free_cards(card_vec* head)
{
    for(unsigned i = 0; i < head->size; i++)
    {
        SDL_DestroyTexture(head->data[i]->texture);
        free(head->data[i]);
        free(head->data);
    }
}

ErrorCode check_duplicate(card_vec* head, card_entry* new_card)
{
    for(unsigned i = 0; i < head->size; i++)
    {
        if(strncmp(head->data[i]->name, new_card->name, MAX_NAME_LEN) == 0)
            return ERR_CARD_DUP;
    }

    return ERR_OK;
}
