#include "textures.h"

card_vec cards = {0};
SDL_Texture *bar, *button;

ErrorCode load_all_textures()
{
    ErrorCode card_err = load_card_data(&cards, window_state.renderer);
    if(card_err != ERR_OK)
    {
        return card_err;
    }

    if(load_texture(&bar, window_state.renderer, "assets/bar.bmp") != ERR_OK)
    {
        strcpy(error_msg, "Couldn't load the bar texture");
        return ERR_TEXTURE;
    }

    if(load_texture(&button, window_state.renderer, "assets/button.bmp") != ERR_OK)
    {
        strcpy(error_msg, "Couldn't load the button texture");
        return ERR_TEXTURE;
    }

    return ERR_OK;
}

void free_all_textures()
{
    free_cards(&cards);
    SDL_DestroyTexture(bar);
    SDL_DestroyTexture(button);
}
