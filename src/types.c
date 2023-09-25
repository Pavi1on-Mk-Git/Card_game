#include "types.h"

#include "globals.h"

#include <string.h>

void push_back(card_vec* head, card_entry* new_card)
{
    if(head->size == head->capacity)
        head->data = realloc(
            head->data, sizeof(card_entry) * (head->capacity ? (head->capacity *= 2) : (head->capacity = 1))
        );

    head->data[head->size++] = *new_card;
}

int compare_cards(void* context, const void* first, const void* second)
{
    UNUSED(context);
    const card_entry* first_card = (const card_entry*) first;
    const card_entry* second_card = (const card_entry*) second;
    return strncmp(first_card->name, second_card->name, MAX_NAME_LEN);
}

void sort_vec(card_vec* head)
{
    qsort_s(head->data, head->size, sizeof(card_entry), compare_cards, NULL);
}

void free_cards(card_vec* head)
{
    for(unsigned i = 0; i < head->size; i++)
    {
        SDL_DestroyTexture(head->data[i].texture);
        free(head->data);
    }
}

ErrorCode check_duplicate(card_vec* head, card_entry* new_card)
{
    for(unsigned i = 0; i < head->size; i++)
    {
        if(strncmp(head->data[i].name, new_card->name, MAX_NAME_LEN) == 0)
            return ERR_CARD_DUP;
    }

    return ERR_OK;
}
