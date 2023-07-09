#include "game_loop.h"

int main(int argc, char*argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    SDL_Window* window;
    SDL_Renderer* renderer;

    if(initialize_SDL(&window, &renderer) != 0)
        return 1;

    game_loop(renderer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
