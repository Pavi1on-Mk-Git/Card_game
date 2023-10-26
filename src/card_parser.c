#include "card_parser.h"

#include "loading.h"

#include <string.h>

void parse_card_data(card_entry* card, FILE* card_data, ErrorCode* err)
{
    char buffer[MAX_NAME_LEN + 1];
    int offset;
    char* strtok_s_state;

    fgets(buffer, MAX_NAME_LEN, card_data);

    // Check for opening brace
    if(strncmp(buffer, "{\n", MAX_NAME_LEN) != 0)
    {
        *err = ERR_FILE_FORMAT;
        return;
    }

    fgets(buffer, MAX_NAME_LEN, card_data);

    // Check file formatting
    if(strncmp(strtok_s(buffer, "\n\t: ", &strtok_s_state), "file_name", MAX_NAME_LEN) != 0)
    {
        *err = ERR_FILE_FORMAT;
        return;
    }

    // Load relative path to file
    offset = strlen("assets/cards/");
    if(memmove_s(buffer + offset, sizeof(buffer), strtok_s(NULL, "\n\t: ", &strtok_s_state), MAX_NAME_LEN - offset) !=
       0)
    {
        *err = ERR_FILE_FORMAT;
        return;
    }
    if(memcpy_s(buffer, sizeof(buffer), "assets/cards/", offset))
    {
        *err = ERR_FILE_FORMAT;
        return;
    }

    // Load the texture based on relative path from buffer
    SDL_Texture* texture = load_texture(buffer, err);
    if(*err != ERR_OK)
        return;
    card->texture = texture;

    fgets(buffer, MAX_NAME_LEN, card_data);

    // Check file formatting
    if(strncmp(strtok_s(buffer, "\n\t: ", &strtok_s_state), "card_name", MAX_NAME_LEN) != 0)
    {
        *err = ERR_FILE_FORMAT;
        return;
    }

    // Load card name from buffer
    strncpy(card->name, strtok_s(NULL, "\n\t: ", &strtok_s_state), MAX_NAME_LEN);

    fgets(buffer, MAX_NAME_LEN, card_data);

    // Check file formatting
    if(strncmp(strtok_s(buffer, "\n\t: ", &strtok_s_state), "cutout_rect", MAX_NAME_LEN) != 0)
    {
        *err = ERR_FILE_FORMAT;
        return;
    }

    // Load texture cutout rectangle from buffer
    if((card->cutout_rect.x = atoi(strtok_s(NULL, "\n\t: ", &strtok_s_state))) == 0)
    {
        *err = ERR_FILE_FORMAT;
        return;
    }

    if((card->cutout_rect.y = atoi(strtok_s(NULL, "\n\t: ", &strtok_s_state))) == 0)
    {
        *err = ERR_FILE_FORMAT;
        return;
    }

    if((card->cutout_rect.w = atoi(strtok_s(NULL, "\n\t: ", &strtok_s_state))) == 0)
    {
        *err = ERR_FILE_FORMAT;
        return;
    }

    if((card->cutout_rect.h = atoi(strtok_s(NULL, "\n\t: ", &strtok_s_state))) == 0)
    {
        *err = ERR_FILE_FORMAT;
        return;
    }

    fgets(buffer, MAX_NAME_LEN, card_data);

    // Check for closing brace
    if(strcmp(buffer, "}\n") != 0)
    {
        *err = ERR_FILE_FORMAT;
        return;
    }
}
