#ifndef UI_TREE_H
#define UI_TREE_H

#include "error_code.h"

#include <SDL2/SDL.h>

typedef enum
{
    NONE,
    TEXTURE,
    COLOUR,
    OTHER,
} DrawType;

typedef struct
{
    SDL_bool hidden : 1;
} UiNodeBitmap;

typedef struct UiNode
{
    SDL_FRect viewport;
    DrawType draw_type;

    union
    {
        SDL_Texture* texture;
        SDL_Colour colour;
        void (*draw)(const struct UiNode*);
    };

    UiNodeBitmap state;
    void (*handle)(const struct UiNode*);
    unsigned char children_size;
    struct UiNode* children;
} UiNode;

UiNode* ui_tree_init(ErrorCode* err);
void ui_tree_free(UiNode* root);

void ui_tree_transform(UiNode* node, const SDL_FPoint* offset);

#endif
