#include "card_vec.h"
#include "game_loop.h"
#include "player_state.h"
#include "viewports.h"
#include "window_state.h"


WindowState window_state = {0};
card_vec cards = {0};

int main(int argc, char* argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    ErrorCode err = ERR_OK;

    initialize_SDL(&window_state.window, &window_state.renderer, &err);

    if(err != ERR_OK)
        return 1;

    window_state.ui_tree = ui_tree_init(&err);

    if(err != ERR_OK)
    {
        SDL_Log(error_msg);
    }

    setup_viewports();

    init_player_state();

    game_loop(&err);

    ui_tree_free(window_state.ui_tree);
    free_cards(&cards);
    SDL_DestroyRenderer(window_state.renderer);
    SDL_DestroyWindow(window_state.window);
    SDL_Quit();

    return 0;
}
