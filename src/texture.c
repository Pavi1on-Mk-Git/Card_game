#include "texture.h"

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

ErrorCode load_card_data(card** head, SDL_Renderer* renderer)
{
    FILE* card_data = fopen("assets/cards/card_data.bruh", "r");
    card_entry* curr_card;
    int next_char;

    do
    {
        if(parse_card_data(&curr_card, card_data, renderer) != ERR_OK)
        {
            strncpy(error_msg, "Card data file format error", MAX_NAME_LEN);
            return ERR_FILE_FORMAT;
        }

        if(check_duplicate(head, curr_card) != ERR_OK)
        {
            strncpy(error_msg, "Duplicate card found", MAX_NAME_LEN);
            return ERR_FILE_FORMAT;
        }

        add(head, &curr_card);

        next_char = fgetc(card_data);
        ungetc(next_char, card_data);
    }
    while(next_char != EOF);

    fclose(card_data);

    return ERR_OK;
}