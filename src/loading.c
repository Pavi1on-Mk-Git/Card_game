#include "loading.h"

#include "card_parser.h"

#include <string.h>

ErrorCode load_texture(SDL_Texture** texture, SDL_Renderer* renderer, const char* path)
{
    SDL_Surface* surface = SDL_LoadBMP(path);

    if(surface == NULL)
    {
        SDL_FreeSurface(surface);
        return ERR_FILE_FORMAT;
    }

    if((*texture = SDL_CreateTextureFromSurface(renderer, surface)) == NULL)
    {
        SDL_FreeSurface(surface);
        return ERR_SDL;
    }

    SDL_FreeSurface(surface);
    return ERR_OK;
}

ErrorCode load_card_data(card_vec* head, SDL_Renderer* renderer)
{
    if(!head)
        return ERR_NULL;

    FILE* card_data = fopen("assets/cards/card_data.bruh", "r");
    int next_char;

    do
    {
        card_entry* curr_card = calloc(1, sizeof(card_entry));

        if(parse_card_data(curr_card, card_data, renderer) != ERR_OK)
        {
            strncpy(error_msg, "Card data file format error", MAX_NAME_LEN);
            SDL_DestroyTexture(curr_card->texture);
            free(curr_card);
            return ERR_FILE_FORMAT;
        }

        if(check_duplicate(head, curr_card) != ERR_OK)
        {
            strncpy(error_msg, "Duplicate card found", MAX_NAME_LEN);
            SDL_DestroyTexture(curr_card->texture);
            free(curr_card);
            return ERR_FILE_FORMAT;
        }

        push_back(head, curr_card);

        next_char = fgetc(card_data);
        ungetc(next_char, card_data);
    }
    while(next_char != EOF);

    sort_vec(head);

    fclose(card_data);

    return ERR_OK;
}
