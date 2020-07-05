#include <SDL2/SDL.h>
#include "snake.h"
#include <ctime>
#include <iostream>
#include <vector>

bool isFree(const std::vector<Snake*>& list, const SDL_Rect& apple)
{
	for (Snake* item : list)
	{
		if (item->check_collision(apple)) return true;
	}
	return false;
}

int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	srand(time(NULL));
	
	bool isWork = true;

	unsigned int w = 600;
	unsigned int h = 600;
	int range = w / 20;
	
	SDL_Window* window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	std::vector<Snake*> list;

// Objects creating
	Player* player = new Player(renderer, 0, 255, 0, 0, 0, w, h, range);
	Snake* bot = new Snake(renderer, 0, 0, 255, range * 5, 0, w, h, range);

// Adding objects to vector
	list.push_back(player);
	list.push_back(bot);

	SDL_Rect apple;
   	
	do
	{
		apple.x = rand()%(w / range) * range;
		apple.y = rand()%(h / range) * range;
		apple.w = range;
	   	apple.h = range;
	} while(isFree(list, apple));

	SDL_Event event;

// FPS control
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

			for (Snake* i : list)
			{
				if (i->eat_apple(apple))
				{
					do
					{
						apple.x = rand()%(w/range) * range;
						apple.y = rand()%(h/range) * range;
					} while (isFree(list, apple));
				}
			}

			// Move all objects
			for (Snake* item : list)
			{
				item->move();
			}
			// Check collision
			for (Snake* item : list)
			{
				if (!item->check(list))
				{
					isWork = false;
					break;
				}
			}
			// Render objects
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
			SDL_RenderFillRect(renderer, &apple);
			for (Snake* item : list)
			{
				item->render();
			}
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
		player->motion(event);
		for (Snake* item : list)
		{
			if (item != player)
			{
				item->motion(apple);
			}
		}
		end = clock();
	}

	for (Snake* item : list)
	{
		delete item;
	}

	return 0;
}
