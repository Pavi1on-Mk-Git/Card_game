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

void game_loop(SDL_Renderer* renderer)
{
	SDL_Texture* text = load_card(renderer, "cards/edgy_1.bmp");

	SDL_Rect card;

	SDL_QueryTexture(text, NULL, NULL, &card.w, &card.h);

	card.x = SCREEN_WIDTH / 2 - card.w / 2;
	card.y = SCREEN_HEIGHT / 2 - card.h / 2;

	SDL_RenderCopyEx(renderer, text, NULL, &card, 0, NULL, SDL_FLIP_NONE);

	SDL_RenderPresent(renderer);

	SDL_bool quit = SDL_FALSE;
	SDL_Event event;

	while(quit == SDL_FALSE)
	{
		if(SDL_WaitEvent(&event))
            if(event.type == SDL_QUIT)
                quit = SDL_TRUE;
	}
}
