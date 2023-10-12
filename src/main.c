#include "game_loop.h"
#include "player_state.h"
#include "textures.h"
#include "viewports.h"
#include "window_state.h"

WindowState window_state = {0};

int main(int argc, char* argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    if(initialize_SDL(&window_state.window, &window_state.renderer) != 0)
        return 1;

    setup_viewports();

    init_player_state();

    game_loop(&window_state);

    free_all_interactables();
    SDL_DestroyRenderer(window_state.renderer);
    SDL_DestroyWindow(window_state.window);
    SDL_Quit();

    return 0;
}
