#include <SDL2/SDL.h>
#include "function.h"
#include <SDL2/SDL_keyboard.h>
#include <ctime>
#include <iostream>

int main()
{
	bool isWork = true;

	unsigned int w = 600;
	unsigned int h = 600;

	SDL_Window* window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	unsigned int size = 1;
	unsigned int range = w / 30;

	SDL_Point dir = {1,0};
	SDL_Rect* rect = new SDL_Rect[size];

	srand(time(NULL));

	SDL_Rect apple = {rand()%(w/range)* range, rand()%(h/range) * range, range, range};

	for (int i = 0 ; i < size ; i++)
	{
		rect[i] = {-i * range, 0, w/30, w/30};
	}
	SDL_Event event;
	time_t start = clock();
	time_t end = clock();
	
	double FPS = 10;
	double delay = 1000 / FPS;

	double SPF;

	while(isWork)
	{
		SPF = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;
		if (SPF < delay) SDL_Delay(delay - SPF);
		start = clock();

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		if (eat_apple(size, rect, apple, range))
		{
			apple.x = rand()%(w/range) * range;
			apple.y = rand()%(h/range) * range;
		}
		isWork = snake_check(size, rect);
		snake_move(size, rect, dir, range, w, h);
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
		SDL_RenderFillRect(renderer, &apple);
		snake_render(renderer, size, rect);
		while (SDL_PollEvent(&event))
		{
			const Uint8* state = SDL_GetKeyboardState(NULL);
			if (event.type == SDL_QUIT)
			{
				isWork = false;
				break;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				if (state[SDL_SCANCODE_W] && dir.y != 1) 
				{
					dir.x = 0;
					dir.y = -1;
				}
				if (state[SDL_SCANCODE_A] && dir.x != 1)
				{
					dir.x = -1;
					dir.y = 0;
				}
				if (state[SDL_SCANCODE_S] && dir.y != -1)
				{
					dir.x = 0;
					dir.y = 1;
				}
				if (state[SDL_SCANCODE_D] && dir.x != -1)
				{
					dir.x = 1;
					dir.y = 0;
				}
				
				if (state[SDL_SCANCODE_ESCAPE])
				{
					isWork = false;
					break;
				}
			}
		}

		SDL_RenderPresent(renderer);
		end = clock();
	}

	delete[]rect;
	
	return 0;
}
