#include "card_parser.h"

#include "texture.h"

#include <string.h>

ErrorCode parse_card_data(card_entry* card, FILE card_data[static 1], SDL_Renderer* renderer)
{
    char buffer[MAX_NAME_LEN + 1];
    int offset;
    char* strtok_s_state;

    fgets(buffer, MAX_NAME_LEN, card_data);

    // Check for opening brace
    if(strncmp(buffer, "{\n", MAX_NAME_LEN) != 0)
        return ERR_FILE_FORMAT;

    fgets(buffer, MAX_NAME_LEN, card_data);

    // Check file formatting
    if(strncmp(strtok_s(buffer, "\n\t: ", &strtok_s_state), "file_name", MAX_NAME_LEN) != 0)
        return ERR_FILE_FORMAT;

    // Load relative path to file
    offset = strlen("assets/cards/");
    if(memmove_s(buffer + offset, sizeof(buffer), strtok_s(NULL, "\n\t: ", &strtok_s_state), MAX_NAME_LEN - offset) !=
       0)
        return ERR_FILE_FORMAT;
    if(memcpy_s(buffer, sizeof(buffer), "assets/cards/", offset))
        return ERR_FILE_FORMAT;

    // Load the texture based on relative path from buffer
    SDL_Texture* texture;
    if(load_texture(&texture, renderer, buffer) != ERR_OK)
        return ERR_FILE_FORMAT;
    card->texture = texture;

    fgets(buffer, MAX_NAME_LEN, card_data);

    // Check file formatting
    if(strncmp(strtok_s(buffer, "\n\t: ", &strtok_s_state), "card_name", MAX_NAME_LEN) != 0)
        return ERR_FILE_FORMAT;

    // Load card name from buffer
    strncpy(card->name, strtok_s(NULL, "\n\t: ", &strtok_s_state), MAX_NAME_LEN);

    fgets(buffer, MAX_NAME_LEN, card_data);

    // Check file formatting
    if(strncmp(strtok_s(buffer, "\n\t: ", &strtok_s_state), "cutout_rect", MAX_NAME_LEN) != 0)
        return ERR_FILE_FORMAT;

    // Load texture cutout rectangle from buffer
    card->cutout_rect = (SDL_Rect
    ){.x = atoi(strtok_s(NULL, "\n\t: ", &strtok_s_state)),
      .y = atoi(strtok_s(NULL, "\n\t: ", &strtok_s_state)),
      .w = atoi(strtok_s(NULL, "\n\t: ", &strtok_s_state)),
      .h = atoi(strtok_s(NULL, "\n\t: ", &strtok_s_state))};

    fgets(buffer, MAX_NAME_LEN, card_data);

    // Check for closing brace
    if(strcmp(buffer, "}\n") != 0)
        return ERR_FILE_FORMAT;

    return ERR_OK;
}
