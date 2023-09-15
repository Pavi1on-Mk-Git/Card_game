#include <ctype.h>

#include "card_parser.h"
#include "helpers.h"

ErrorCode read_field(FILE card_data[static 1], const char* field_name, char* buffer, const char* buffer_start, const char* buffer_end)
{
    int c;
    size_t offset = 0;

    while(isspace(c = getc(card_data))){}

    ungetc(c, card_data);

    if(read_until(card_data, buffer, ':', 0) != ERR_OK)
        return ERR_FILE_FORMAT;

    if(strncmp(buffer, field_name, MAX_NAME_LEN) != 0)
        return ERR_FILE_FORMAT;

    fgetc(card_data);

    if(buffer_start)
    {
        snprintf(buffer, MAX_NAME_LEN, buffer_start);

        offset = strlen(buffer);
    }

    if(read_until(card_data, buffer, '\n', offset) != ERR_OK)
        return ERR_FILE_FORMAT;

    if(buffer_end)
        strncat(buffer, buffer_end, MAX_NAME_LEN - strlen(buffer));

    return ERR_OK;
}

ErrorCode parse_card_data(card_entry** card, FILE card_data[static 1], SDL_Renderer* renderer)
{
    char buffer[MAX_NAME_LEN];

    card_entry* to_add = malloc(sizeof(card_entry));

    fgets(buffer, MAX_NAME_LEN, card_data);

    if(strncmp(buffer, "{\n", MAX_NAME_LEN) != 0)
        return ERR_FILE_FORMAT;

    if(read_field(card_data, "file_name", buffer, "assets/cards/", ".bmp") != ERR_OK)
        return ERR_FILE_FORMAT;

    SDL_Texture* texture;

    if(load_texture(&texture, renderer, buffer) != ERR_OK)
        return ERR_FILE_FORMAT;

    to_add->texture = texture;

    if(read_field(card_data, "card_name", buffer, NULL, NULL) != ERR_OK)
        return ERR_FILE_FORMAT;

    strcpy(to_add->name, buffer);

    fgets(buffer, MAX_NAME_LEN, card_data);

    if(strcmp(buffer, "}\n") != 0)
        return ERR_FILE_FORMAT;

    *card = to_add;

    return ERR_OK;
}