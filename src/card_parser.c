#include "card_parser.h"

ErrorCode parse_card_data(card_entry** card, FILE card_data[static 1], SDL_Renderer* renderer)
{
    char buffer[MAX_NAME_LEN + 1];
    int offset;
    card_entry* to_add = malloc(sizeof(card_entry));

    fgets(buffer, MAX_NAME_LEN, card_data);

    // Check for opening brace
    if(strncmp(buffer, "{\n", MAX_NAME_LEN) != 0)
        return ERR_FILE_FORMAT;

    fgets(buffer, MAX_NAME_LEN, card_data);

    // Check file formatting
    if(strncmp(strtok(buffer, "\n\t: "), "file_name", MAX_NAME_LEN) != 0)
        return ERR_FILE_FORMAT;

    // Load relative path to file
    offset = strlen("assets/cards/");
    memmove(buffer + offset, strtok(NULL, "\n\t: "), MAX_NAME_LEN - offset);
    memcpy(buffer, "assets/cards/", offset);

    // Load the texture based on relative path from buffer
    SDL_Texture* texture;
    if(load_texture(&texture, renderer, buffer) != ERR_OK)
        return ERR_FILE_FORMAT;
    to_add->texture = texture;

    fgets(buffer, MAX_NAME_LEN, card_data);

    // Check file formatting
    if(strncmp(strtok(buffer, "\n\t: "), "card_name", MAX_NAME_LEN) != 0)
        return ERR_FILE_FORMAT;

    // Load card name from buffer
    strncpy(to_add->name, strtok(NULL, "\n\t: "), MAX_NAME_LEN);

    fgets(buffer, MAX_NAME_LEN, card_data);

    // Check file formatting
    if(strncmp(strtok(buffer, "\n\t: "), "cutout_rect", MAX_NAME_LEN) != 0)
        return ERR_FILE_FORMAT;

    // Load texture cutout rectangle from buffer
    to_add->cutout_rect = (SDL_Rect
    ){.x = atoi(strtok(NULL, "\n\t: ")),
      .y = atoi(strtok(NULL, "\n\t: ")),
      .w = atoi(strtok(NULL, "\n\t: ")),
      .h = atoi(strtok(NULL, "\n\t: "))};

    fgets(buffer, MAX_NAME_LEN, card_data);

    // Check for closing brace
    if(strcmp(buffer, "}\n") != 0)
        return ERR_FILE_FORMAT;

    *card = to_add;

    return ERR_OK;
}
