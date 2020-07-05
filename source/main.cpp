#include <SDL2/SDL.h>
#include "snake.h"
#include <ctime>
#include <iostream>

int main()
{
	bool isWork = true;

	unsigned int w = 600;
	unsigned int h = 600;

	SDL_Window* window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	int range = w / 20;
	Player player(renderer, w, h, range);

	srand(time(NULL));

	SDL_Rect apple;
   	
	do
	{
		apple = {rand()%(w / range)* range, rand()%(h / range) * range, range, range};
	} while(player.isSnake(apple));

	SDL_Event event;
	time_t start = clock();
	time_t end = clock();
	
	double FPS = 10;
	double delay = 1000 / FPS;

	double SPF;

	while(isWork)
	{
		SPF = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;
		if (SPF > delay)
		{	
			start = clock();

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderClear(renderer);

			if (player.eat_apple(apple))
			{
				do
				{
					apple.x = rand()%(w/range) * range;
					apple.y = rand()%(h/range) * range;
				} while (player.isSnake(apple));
			}
			player.move();
			isWork = player.check();
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
			SDL_RenderFillRect(renderer, &apple);
			player.render();
			while (SDL_PollEvent(&event))
			{
				const Uint8* state = SDL_GetKeyboardState(NULL);
				if (event.type == SDL_QUIT)
				{
					isWork = false;
					break;
				}


				if (state[SDL_SCANCODE_ESCAPE])
				{
					isWork = false;
					break;
				}
			}

			SDL_RenderPresent(renderer);
		}
		player.motion(event);			
		end = clock();
	}

	return 0;
}
