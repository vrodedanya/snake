#include <SDL2/SDL.h>
#include "function.h"

int main()
{
	bool isWork = true;

	unsigned int w = 600;
	unsigned int h = 600;

	SDL_Window* window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	int size = 1;
	unsigned int range = w / 30;

	SDL_Point dir = {1,0};
	SDL_Rect* rect = new SDL_Rect[size];

	rect[size - 1] = {0, 0, w/30, w/30};
	SDL_Event event;

	while(isWork)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		isWork = snake_check(size,rect);
		snake_move(size, rect, dir, range);
		snake_render(renderer, size, rect);
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				isWork = false;
				break;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_w:
					dir.x = 0;
					dir.y = -1;
					break;
					case SDLK_a:
					dir.x = -1;
					dir.y = 0;
					break;
					case SDLK_s:
					dir.x = 0;
					dir.y = 1;
					break;
					case SDLK_d:
					dir.x = 1;
					dir.y = 0;
					break;
				}
			}
		}

		SDL_RenderPresent(renderer);
	}

	delete[]rect;
	
	return 0;
}
