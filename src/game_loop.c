#include "game_loop.h"

ErrorCode initialize_SDL(SDL_Window* window[static 1], SDL_Renderer* renderer[static 1])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
  	{
    	SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL Initialization failed: %s\n", SDL_GetError());
    	return ERR_INIT;
  	}

    *window = SDL_CreateWindow("Card game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      	SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL)
  	{
    	SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Window creation failed: %s\n", SDL_GetError());
    	return ERR_INIT;
  	}

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
  	{
    	SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Renderer creation failed: %s\n", SDL_GetError());
    	return ERR_INIT;
  	}

    return ERR_OK;
}

void game_loop(SDL_Renderer* renderer)
{
	SDL_bool quit = SDL_FALSE;
	SDL_Event event;
	Uint64 frame_start, frame_time;

	card* textures = {0};
	
	if(load_cards(&textures, renderer) != ERR_OK)
	{
		puts(error_msg);
		return;
	}

	card* curr_text = textures;

	while(quit == SDL_FALSE)
	{
		frame_start = SDL_GetTicks64();

		while(SDL_PollEvent(&event))
            if(event.type == SDL_QUIT)
                quit = SDL_TRUE;

			SDL_Rect card;

			SDL_RenderClear(renderer);

			SDL_QueryTexture((SDL_Texture*)curr_text->data->texture, NULL, NULL, &card.w, &card.h);

			card.w = card.w / 2;
			card.h = card.h / 2;
			card.x = SCREEN_WIDTH / 2 - card.w / 2;
			card.y = SCREEN_HEIGHT / 2 - card.h / 2;

			SDL_RenderCopyEx(renderer, (SDL_Texture*)curr_text->data->texture, NULL, &card, 0, NULL, SDL_FLIP_NONE);

			SDL_RenderPresent(renderer);

			frame_time = SDL_GetTicks64() - frame_start;

    	if(frame_time < FRAME_TIME)
    	{
        	SDL_Delay(FRAME_TIME - frame_time);
    	}
	}
}
