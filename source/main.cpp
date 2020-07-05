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

	Player player(renderer, 0, 0, w, h, range);
	Snake bot(renderer, range * 5, 0, w, h, range);

	srand(time(NULL));

	SDL_Rect apple;
   	
	do
	{
		apple.x = rand()%(w / range) * range;
		apple.y = rand()%(h / range) * range;
		apple.w = range;
	   	apple.h = range;
	} while(player.isSnake(apple) || bot.isSnake(apple));

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
			if (bot.eat_apple(apple))
			{
				do
				{
					apple.x = rand()%(w/range) * range;
					apple.y = rand()%(h/range) * range;
				} while (player.isSnake(apple));
			}
			// Move all objects
			player.move();
			bot.move();
			// Check collision
			isWork = player.check();
			// Render objects
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
			SDL_RenderFillRect(renderer, &apple);
			player.render();
			bot.render();

			// EventHandler
			while (SDL_PollEvent(&event))
			{
				const Uint8* state = SDL_GetKeyboardState(NULL);
				if (event.type == SDL_QUIT)
				{
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
		bot.motion(apple);
		end = clock();
	}

	return 0;
}
