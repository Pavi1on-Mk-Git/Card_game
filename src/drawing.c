#include "drawing.h"

SDL_Texture* load_card(SDL_Renderer* renderer, const char* path)
{
    SDL_RWops* stream = SDL_RWFromFile(path, "r");
    SDL_Surface* surface = SDL_LoadBMP_RW(stream, 1);
    return SDL_CreateTextureFromSurface(renderer, surface);
}