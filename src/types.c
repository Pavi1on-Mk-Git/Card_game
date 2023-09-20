#include "types.h"

#include "globals.h"

#include <string.h>

void add(card** head, card_entry** new_card)
{
    card* new_entry = malloc(sizeof(card));

    new_entry->data = *new_card;
    new_entry->next = NULL;

    if(*head == NULL)
    {
        *head = new_entry;
        return;
    }

    card* curr = *head;

    while(curr->next != NULL)
        curr = curr->next;

    curr->next = new_entry;
}

void free_cards(card** head)
{
    card* curr = *head;
    card* next = curr->next;

    while(next != NULL)
    {
        SDL_DestroyTexture(curr->data->texture);
        free(curr->data);
        free(curr);

        curr = next;
        next = curr->next;
    }
}

ErrorCode check_duplicate(card** head, card_entry* new_card)
{
    card* curr = *head;
    while(curr != NULL)
    {
        if(strncmp(curr->data->name, new_card->name, MAX_NAME_LEN) == 0)
            return ERR_CARD_DUP;

        curr = curr->next;
    }

    return ERR_OK;
}
