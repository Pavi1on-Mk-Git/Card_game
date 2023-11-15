#include "event_handlers.h"

#include "helpers.h"
#include "player_state.h"
#include "viewports.h"
#include "window_state.h"

void handle_all(const UiNode* root)
{
    if(!root)
        return;

    if(root->state.hidden)
        return;

    if(root->handle)
        root->handle(root);

    for(int i = 0; i < root->children_size; i++)
        handle_all(&root->children[i]);
}

void handle_top_bar(const UiNode* bar)
{
    switch(window_state.event.type)
    {
    case SDL_MOUSEBUTTONDOWN:

        if(window_state.event.button.button == SDL_BUTTON_LEFT)
        {
            SDL_FPoint mouse;

            get_logical_mouse(&mouse.x, &mouse.y);

            if(SDL_PointInFRect(&mouse, &bar->viewport))
            {
                SDL_Point real_mouse;

                SDL_GetGlobalMouseState(&real_mouse.x, &real_mouse.y);
                SDL_GetWindowPosition(window_state.window, &window_state.mouse_offset.x, &window_state.mouse_offset.y);
                window_state.mouse_offset.x -= real_mouse.x;
                window_state.mouse_offset.y -= real_mouse.y;
                window_state.dragging = SDL_TRUE;
            }
        }
        break;

    case SDL_MOUSEMOTION:

        if(window_state.dragging)
        {
            SDL_Point real_mouse;
            SDL_GetGlobalMouseState(&real_mouse.x, &real_mouse.y);
            SDL_SetWindowPosition(
                window_state.window, real_mouse.x + window_state.mouse_offset.x,
                real_mouse.y + window_state.mouse_offset.y
            );
        }
        break;

    case SDL_MOUSEBUTTONUP:

        if(window_state.event.button.button == SDL_BUTTON_LEFT)
            window_state.dragging = SDL_FALSE;
        break;
    }
}

void handle_exit_button(const UiNode* exit_button)
{
    switch(window_state.event.type)
    {
    case SDL_MOUSEBUTTONDOWN:

        if(window_state.event.button.button == SDL_BUTTON_LEFT)
        {
            SDL_FPoint mouse;

            get_logical_mouse(&mouse.x, &mouse.y);

            if(SDL_PointInFRect(&mouse, &exit_button->viewport))
                window_state.want_exit = SDL_TRUE;
        }
        break;
    case SDL_MOUSEBUTTONUP:

        if(window_state.event.button.button == SDL_BUTTON_LEFT)
        {
            SDL_FPoint mouse;

            get_logical_mouse(&mouse.x, &mouse.y);

            if(window_state.want_exit && SDL_PointInFRect(&mouse, &exit_button->viewport))
                window_state.quit = SDL_TRUE;
        }
        break;
    }
}

void handle_fullscreen_button(const UiNode* fullscreen_button)
{
    switch(window_state.event.type)
    {
    case SDL_MOUSEBUTTONDOWN:

        if(window_state.event.button.button == SDL_BUTTON_LEFT)
        {
            SDL_FPoint mouse;

            get_logical_mouse(&mouse.x, &mouse.y);

            if(SDL_PointInFRect(&mouse, &fullscreen_button->viewport))
                window_state.want_fullscreen = SDL_TRUE;
        }
        break;

    case SDL_MOUSEBUTTONUP:

        if(window_state.event.button.button == SDL_BUTTON_LEFT)
        {
            window_state.dragging = SDL_FALSE;

            SDL_FPoint mouse;

            get_logical_mouse(&mouse.x, &mouse.y);

            if(window_state.want_fullscreen && SDL_PointInFRect(&mouse, &fullscreen_button->viewport))
            {
                SDL_SetWindowFullscreen(window_state.window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                SDL_RenderSetLogicalSize(window_state.renderer, SCREEN_WIDTH, BASE_SCREEN_HEIGHT);
                window_state.want_fullscreen = SDL_FALSE;
                window_state.is_fullscreen = SDL_TRUE;
                for(unsigned char i = 0; i < 4; i++)
                    window_state.ui_tree->children[i].state.hidden = SDL_TRUE;
                ui_tree_transform(&window_state.ui_tree->children[4], &(const SDL_FPoint){.y = -BAR_HEIGHT});
            }
        }
        break;
    }
}

void handle_min_button(const UiNode* min_button)
{
    switch(window_state.event.type)
    {
    case SDL_MOUSEBUTTONDOWN:

        if(window_state.event.button.button == SDL_BUTTON_LEFT)
        {
            SDL_FPoint mouse;

            get_logical_mouse(&mouse.x, &mouse.y);

            if(SDL_PointInFRect(&mouse, &min_button->viewport))
                window_state.want_min = SDL_TRUE;
        }
        break;

    case SDL_MOUSEBUTTONUP:

        if(window_state.event.button.button == SDL_BUTTON_LEFT)
        {
            window_state.dragging = SDL_FALSE;

            SDL_FPoint mouse;

            get_logical_mouse(&mouse.x, &mouse.y);

            if(window_state.want_min && SDL_PointInFRect(&mouse, &min_button->viewport))
            {
                SDL_MinimizeWindow(window_state.window);
                window_state.want_min = SDL_FALSE;
            }
        }
        break;
    }
}

void handle_esc()
{
    switch(window_state.event.type)
    {
    case SDL_KEYUP:

        if(window_state.is_fullscreen && window_state.event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
        {
            SDL_SetWindowFullscreen(window_state.window, 0);
            window_state.is_fullscreen = SDL_FALSE;
            for(unsigned char i = 0; i < 4; i++)
                window_state.ui_tree->children[i].state.hidden = SDL_FALSE;
            ui_tree_transform(&window_state.ui_tree->children[4], &(const SDL_FPoint){.y = BAR_HEIGHT});
        }
        break;
    }
}

void handle_draw_button(const UiNode* draw_button)
{
    switch(window_state.event.type)
    {
    case SDL_MOUSEBUTTONUP:
        if(window_state.event.button.button == SDL_BUTTON_LEFT)
        {
            SDL_FPoint mouse;

            get_logical_mouse(&mouse.x, &mouse.y);

            if(SDL_PointInFRect(&mouse, &draw_button->viewport))
            {
                if(player_state.hand.curr_size < MAX_HAND_SIZE)
                    player_state.hand.cards[player_state.hand.curr_size++] = cards.data[rand() % cards.size];
            }
        }
        break;
    }
}

void handle_card_grab(const UiNode* hand)
{
    UNUSED(hand);
    switch(window_state.event.type)
    {
    case SDL_MOUSEBUTTONDOWN:
        if(window_state.event.button.button == SDL_BUTTON_LEFT)
        {
            for(int i = player_state.hand.curr_size - 1; i >= 0; i--)
            {
                if(mouse_in_rotated_rect(
                       &player_state.hand.metadata.dest_rect,
                       &(SDL_FPoint
                       ){.x = player_state.hand.metadata.rot_center.x + player_state.hand.metadata.dest_rect.x,
                         .y = player_state.hand.metadata.rot_center.y + player_state.hand.metadata.dest_rect.y},
                       player_state.hand.metadata.angles[i]
                   ))
                {
                    player_state.hand.metadata.card_grab_bitmap[i] = SDL_TRUE;
                    break;
                }
            }
        }
        break;
    case SDL_MOUSEBUTTONUP:
        if(window_state.event.button.button == SDL_BUTTON_LEFT)
        {
            memset(player_state.hand.metadata.card_grab_bitmap, 0, sizeof(player_state.hand.metadata.card_grab_bitmap));
        }
        break;
    }
}
