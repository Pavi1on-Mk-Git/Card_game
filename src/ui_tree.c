#include "ui_tree.h"

#include "constants.h"
#include "drawing.h"
#include "event_handlers.h"
#include "loading.h"

#include <stdlib.h>

UiNode* ui_tree_init(ErrorCode* err)
{
    UiNode* root = calloc(1, sizeof(UiNode));

    if(root == NULL)
    {
        error_msg = "Memory allocation failed";
        ui_tree_free(root);
        *err = ERR_INIT;
        return NULL;
    }

    *root = (UiNode){
        .viewport =
            (SDL_FRect){
                .x = 0,
                .y = 0,
                .w = SCREEN_WIDTH,
                .h = SCREEN_HEIGHT,
            },
        .draw_type = NONE,
        .children_size = 5,
        .children = calloc(1, sizeof(UiNode) * 5),
    };

    if(root->children == NULL)
    {
        error_msg = "Memory allocation failed";
        ui_tree_free(root);
        *err = ERR_INIT;
        return NULL;
    }

#define TOP_BAR root->children[0]

    TOP_BAR = (UiNode){
        .viewport =
            (SDL_FRect){
                .x = 0,
                .y = 0,
                .w = SCREEN_WIDTH,
                .h = BAR_HEIGHT,
            },
        .draw_type = TEXTURE,
        .texture = load_texture("assets/bar.bmp", err),
        .handle = handle_top_bar,
    };

    if(*err != ERR_OK)
    {
        error_msg = "Couldn't load the bar texture";
        ui_tree_free(root);
        *err = ERR_TEXTURE;
        return NULL;
    }

#define EXIT_BUTTON root->children[1]

    EXIT_BUTTON = (UiNode){
        .viewport =
            (SDL_FRect){
                .x = SCREEN_WIDTH - BUTTON_WIDTH,
                .y = 0,
                .w = BUTTON_WIDTH,
                .h = BAR_HEIGHT,
            },
        .draw_type = TEXTURE,
        .texture = load_texture("assets/exit_button.bmp", err),
        .handle = handle_exit_button,
    };

    if(*err != ERR_OK)
    {
        error_msg = "Couldn't load the exit button texture";
        ui_tree_free(root);
        *err = ERR_TEXTURE;
        return NULL;
    }

#define FULLSCREEN_BUTTON root->children[2]

    FULLSCREEN_BUTTON = (UiNode){
        .viewport =
            (SDL_FRect){
                .x = EXIT_BUTTON.viewport.x - BUTTON_WIDTH,
                .y = 0,
                .w = BUTTON_WIDTH,
                .h = BAR_HEIGHT,
            },
        .draw_type = TEXTURE,
        .texture = load_texture("assets/fullscreen_button.bmp", err),
        .handle = handle_fullscreen_button,
    };

    if(*err != ERR_OK)
    {
        error_msg = "Couldn't load the fullscreen button texture";
        ui_tree_free(root);
        *err = ERR_TEXTURE;
        return NULL;
    }

#define MIN_BUTTON root->children[3]

    MIN_BUTTON = (UiNode){
        .viewport =
            (SDL_FRect){
                .x = FULLSCREEN_BUTTON.viewport.x - BUTTON_WIDTH,
                .y = 0,
                .w = BUTTON_WIDTH,
                .h = BAR_HEIGHT,
            },
        .draw_type = TEXTURE,
        .texture = load_texture("assets/min_button.bmp", err),
        .handle = handle_min_button,
    };

    if(*err != ERR_OK)
    {
        error_msg = "Couldn't load the min button texture";
        ui_tree_free(root);
        *err = ERR_TEXTURE;
        return NULL;
    }

#define MAIN_WINDOW root->children[4]

    MAIN_WINDOW = (UiNode){
        .viewport =
            (SDL_FRect){
                .x = 0,
                .y = BAR_HEIGHT,
                .w = SCREEN_WIDTH,
                .h = BASE_SCREEN_HEIGHT,
            },
        .draw_type = NONE,
        .children_size = 2,
        .children = calloc(1, sizeof(UiNode) * 2),
    };

    if(MAIN_WINDOW.children == NULL)
    {
        error_msg = "Memory allocation failed";
        ui_tree_free(root);
        *err = ERR_INIT;
        return NULL;
    }

#define GAME MAIN_WINDOW.children[0]

    GAME = (UiNode){
        .viewport =
            (SDL_FRect){
                .x = 0,
                .y = MAIN_WINDOW.viewport.y,
                .w = MAIN_WINDOW.viewport.w - (3 * BUTTON_WIDTH),
                .h = MAIN_WINDOW.viewport.h,
            },
        .draw_type = COLOUR,
        .colour =
            (SDL_Colour){
                .r = 0x78,
                .g = 0x20,
                .b = 0x1c,
                .a = 0xff,
            },
        .children_size = 1,
        .children = calloc(1, sizeof(UiNode)),
    };

    if(GAME.children == NULL)
    {
        error_msg = "Memory allocation failed";
        ui_tree_free(root);
        *err = ERR_INIT;
        return NULL;
    }

#define HAND GAME.children[0]

    HAND = (UiNode){
        .viewport =
            (SDL_FRect){
                .x = 0.25 * GAME.viewport.w,
                .y = GAME.viewport.y + 0.85 * GAME.viewport.h,
                .w = 0.5 * GAME.viewport.w,
                .h = 0.15 * GAME.viewport.h,
            },
        .draw_type = OTHER,
        .draw = draw_hand,
        .handle = handle_card_grab,
    };

#define RIGHT_BAR MAIN_WINDOW.children[1]

    RIGHT_BAR = (UiNode){
        .viewport =
            (SDL_FRect){
                .x = GAME.viewport.x + GAME.viewport.w,
                .y = GAME.viewport.y,
                .w = MAIN_WINDOW.viewport.w - GAME.viewport.w,
                .h = GAME.viewport.h,
            },
        .draw_type = COLOUR,
        .colour =
            (SDL_Colour){
                .r = 0xc0,
                .g = 0xc0,
                .b = 0xc0,
                .a = 0xff,
            },
        .children_size = 1,
        .children = calloc(1, sizeof(UiNode)),
    };

    if(RIGHT_BAR.children == NULL)
    {
        error_msg = "Memory allocation failed";
        ui_tree_free(root);
        *err = ERR_INIT;
        return NULL;
    }

#define DRAW_BUTTON_ RIGHT_BAR.children[0]

    DRAW_BUTTON_ = (UiNode){
        .viewport =
            (SDL_FRect){
                .x = RIGHT_BAR.viewport.x + 0.1 * RIGHT_BAR.viewport.w,
                .y = RIGHT_BAR.viewport.y + 0.45 * RIGHT_BAR.viewport.h,
                .w = 0.8 * RIGHT_BAR.viewport.w,
                .h = 0.075 * RIGHT_BAR.viewport.h,
            },
        .draw_type = TEXTURE,
        .texture = load_texture("assets/button.bmp", err),
        .handle = handle_draw_button,
    };

    if(*err != ERR_OK)
    {
        error_msg = "Couldn't load the button texture";
        ui_tree_free(root);
        *err = ERR_TEXTURE;
        return NULL;
    }

    return root;
}

void ui_tree_free_children(UiNode* parent)
{
    if(!parent || !parent->children)
        return;

    for(unsigned i = 0; i < parent->children_size; i++)
    {
        ui_tree_free_children(&parent->children[i]);
        if(parent->children[i].draw_type == TEXTURE)
            SDL_DestroyTexture(parent->children[i].texture);
    }
    free(parent->children);
}

void ui_tree_free(UiNode* root)
{
    if(!root)
        return;

    ui_tree_free_children(root);

    free(root);
}

void ui_tree_transform(UiNode* node, const SDL_FPoint* offset)
{
    node->viewport.x += offset->x;
    node->viewport.y += offset->y;

    for(unsigned char i = 0; i < node->children_size; i++)
        ui_tree_transform(&node->children[i], offset);
}
