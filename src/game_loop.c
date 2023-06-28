#include "game_loop.h"

int initialize_SDL(SDL_Window** window, SDL_Renderer** renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
  	{
    	SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL Initialization failed: %s\n", SDL_GetError());
    	return 1;
  	}

    *window = SDL_CreateWindow("Card game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      	SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL)
  	{
    	SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Window creation failed: %s\n", SDL_GetError());
    	return 2;
  	}

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
  	{
    	SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Renderer creation failed: %s\n", SDL_GetError());
    	return 3;
  	}

    return 0;
}


int exit_loop()
{
    SDL_Event event;
    while(SDL_TRUE)
	{
        if(SDL_PollEvent(&event))
            if(event.type == SDL_QUIT)
                break;
	}
	return 0;
}
