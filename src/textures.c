#include "textures.h"

#include "drawing.h"
#include "event_handlers.h"
#include "viewports.h"

card_vec cards;
interactable interactables[INTER_COUNT];

void load_all_interactables(ErrorCode* err)
{
    load_card_data(&cards, err);
    if(*err != ERR_OK)
        return;

    BAR.texture = load_texture("assets/bar.bmp", err);

    if(*err != ERR_OK)
    {
        error_msg = "Couldn't load the bar texture";
        *err = ERR_TEXTURE;
        return;
    }
    BAR.draw = draw_bar;
    BAR.handle = handle_bar;

    DRAW_BUTTON.texture = load_texture("assets/button.bmp", err);

    if(*err != ERR_OK)
    {
        error_msg = "Couldn't load the button texture";
        *err = ERR_TEXTURE;
        return;
    }
    DRAW_BUTTON.draw = draw_draw_button;
    DRAW_BUTTON.handle = handle_draw_button;
}

void free_all_interactables()
{
    free_cards(&cards);
    for(unsigned i = 0; i < INTER_COUNT; i++)
        SDL_DestroyTexture(interactables[i].texture);
}
