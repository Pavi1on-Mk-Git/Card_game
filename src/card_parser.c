#include "card_parser.h"
#include "helpers.h"

ErrorCode parse_card(card_entry** card, FILE card_data[static 1], SDL_Renderer* renderer)
{
    char buffer[MAX_NAME_LEN];
    size_t offset;

    card_entry* to_add = malloc(sizeof(card_entry));

    fgets(buffer, MAX_NAME_LEN, card_data);

    if(strncmp(buffer, "{\n", MAX_NAME_LEN) != 0)
        return ERR_FILE_FORMAT;

    if(read_until(card_data, buffer, ':', 0) != ERR_OK)
        return ERR_FILE_FORMAT;

    if(strncmp(buffer, "    file_name", MAX_NAME_LEN) != 0)
        return ERR_FILE_FORMAT;

    fgetc(card_data);

    snprintf(buffer, MAX_NAME_LEN, "cards/");

    offset = strlen(buffer);

    if(read_until(card_data, buffer, '\n', offset) != ERR_OK)
        return ERR_FILE_FORMAT;

    strncat(buffer, ".bmp", MAX_NAME_LEN - strlen(buffer));

    SDL_Texture* texture;

    if(load_card(&texture, renderer, buffer) != ERR_OK)
        return ERR_FILE_FORMAT;

    to_add->texture = texture;

    if(read_until(card_data, buffer, ':', 0) != ERR_OK)
        return ERR_FILE_FORMAT;

    if(strncmp(buffer, "    card_name", MAX_NAME_LEN) != 0)
        return ERR_FILE_FORMAT;

    fgetc(card_data);

    if(fgets(buffer, MAX_NAME_LEN, card_data) == NULL)
        return ERR_FILE_FORMAT;

    strcpy(to_add->name, buffer);

    fgets(buffer, MAX_NAME_LEN, card_data);

    if(strcmp(buffer, "}\n") != 0)
        return ERR_FILE_FORMAT;

    *card = to_add;

    return ERR_OK;
}