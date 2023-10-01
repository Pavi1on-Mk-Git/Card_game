#include "card_vec.h"

#include <string.h>

void push_back(card_vec* vec, card_entry* new_card)
{
    if(!vec || !new_card)
        return;
    if(vec->size == vec->capacity)
        vec->data = realloc(
            vec->data, sizeof(card_entry*) * (vec->capacity ? (vec->capacity *= 2) : (vec->capacity = 1))
        );

    vec->data[vec->size++] = new_card;
}

int compare_cards(void* context, const void* first, const void* second)
{
    UNUSED(context);
    const card_entry** first_card = (const card_entry**) first;
    const card_entry** second_card = (const card_entry**) second;
    return strncmp((*first_card)->name, (*second_card)->name, MAX_NAME_LEN);
}

void sort_vec(card_vec* vec)
{
    if(vec)
        qsort_s(vec->data, vec->size, sizeof(card_entry*), compare_cards, NULL);
}

void free_cards(card_vec* head)
{
    if(!head)
        return;
    for(unsigned i = 0; i < head->size; i++)
    {
        SDL_DestroyTexture(head->data[i]->texture);
        for(unsigned i = 0; i < head->size; i++)
            free(head->data[i]);
        free(head->data);
    }
}

ErrorCode check_duplicate(const card_vec* vec, const card_entry* new_card)
{
    if(!vec || !new_card)
        return ERR_NULL;
    for(unsigned i = 0; i < vec->size; i++)
    {
        if(strncmp(vec->data[i]->name, new_card->name, MAX_NAME_LEN) == 0)
            return ERR_CARD_DUP;
    }
    return ERR_OK;
}
