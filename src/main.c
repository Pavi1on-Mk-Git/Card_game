#include "game_loop.h"
#include "globals.h"

int main(int argc, char* argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    WindowState window_state = {0};

    if(initialize_SDL(&window_state.window, &window_state.renderer) != 0)
        return 1;

    setup_viewports();

    game_loop(&window_state);

    SDL_DestroyRenderer(window_state.renderer);
    SDL_DestroyWindow(window_state.window);
    SDL_Quit();

    return 0;
}
