#include "loading.h"

#include "card_parser.h"
#include "window_state.h"

#include <string.h>

SDL_Texture* load_texture(const char* path, ErrorCode* err)
{
    SDL_Surface* surface = SDL_LoadBMP(path);

    if(surface == NULL)
    {
        SDL_FreeSurface(surface);
        *err = ERR_FILE_FORMAT;
        return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(window_state.renderer, surface);

    if(texture == NULL)
    {
        *err = ERR_SDL;
    }

    SDL_FreeSurface(surface);
    return texture;
}

void load_card_data(card_vec* head, ErrorCode* err)
{
    FILE* card_data = fopen("assets/cards/card_data.bruh", "r");
    int next_char;

    do
    {
        card_entry* curr_card = calloc(1, sizeof(card_entry));

        if(curr_card == NULL)
        {
            error_msg = "Memory allocation failed";
            fclose(card_data);
            *err = ERR_MEM;
            return;
        }

        parse_card_data(curr_card, card_data, err);

        if(*err != ERR_OK)
        {
            error_msg = "Card data file format error";
            SDL_DestroyTexture(curr_card->texture);
            free(curr_card);
            fclose(card_data);
            *err = ERR_FILE_FORMAT;
            return;
        }

        if(check_duplicate(head, curr_card))
        {
            error_msg = "Duplicate card found";
            SDL_DestroyTexture(curr_card->texture);
            free(curr_card);
            fclose(card_data);
            *err = ERR_FILE_FORMAT;
            return;
        }

        push_back(head, curr_card);

        next_char = fgetc(card_data);
        ungetc(next_char, card_data);
    }
    while(next_char != EOF);

    sort_vec(head);

    fclose(card_data);
}
