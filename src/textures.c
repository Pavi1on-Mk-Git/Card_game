#include "textures.h"

#include "drawing.h"
#include "event_handlers.h"
#include "viewports.h"

card_vec cards;
interactable interactables[INTER_COUNT];

ErrorCode load_all_interactables()
{
    ErrorCode card_err = load_card_data(&cards);
    if(card_err != ERR_OK)
    {
        return card_err;
    }

    if(load_texture(&BAR.texture, "assets/bar.bmp") != ERR_OK)
    {
        strcpy(error_msg, "Couldn't load the bar texture");
        return ERR_TEXTURE;
    }
    BAR.draw = draw_bar;
    BAR.handle = handle_bar;

    if(load_texture(&DRAW_BUTTON.texture, "assets/button.bmp") != ERR_OK)
    {
        strcpy(error_msg, "Couldn't load the button texture");
        return ERR_TEXTURE;
    }
    DRAW_BUTTON.draw = draw_draw_button;
    DRAW_BUTTON.handle = handle_draw_button;

    return ERR_OK;
}

void free_all_interactables()
{
    free_cards(&cards);
    for(unsigned i = 0; i < INTER_COUNT; i++)
        SDL_DestroyTexture(interactables[i].texture);
}
