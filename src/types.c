#include "types.h"
#include "globals.h"

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