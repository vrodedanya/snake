#include "function.h"
#include <iostream>


void snake_move(unsigned int size, SDL_Rect* rect, SDL_Point& dir, unsigned int& range)
{
	SDL_Point buf, add_buf;
	buf.x = rect[0].x;
	buf.y = rect[0].y;
	rect[0].x += range * dir.x;
	rect[0].y += range * dir.y;
	std::cout << rect[0].x << " " << rect[0].y << std::endl;
	for (register unsigned int i = 1 ; i < size ; i++)
	{
		if (i % 2 != 0)
		{
			add_buf.x = rect[i].x;
			add_buf.y = rect[i].y;
			rect[i].x = buf.x;
			rect[i].y = buf.y;
		}
		else
		{
			buf.x = rect[i].x;
			buf.y = rect[i].y;
			rect[i].x = add_buf.x;
			rect[i].y = add_buf.y;
		}
	}
}

bool snake_check(unsigned int size, SDL_Rect* rect)
{
	for(register int unsigned i = 1; i < size ; i++)
	{
		if (rect[0].x == rect[i].x && rect[0].y == rect[i].y) return false;
	}
	return true;
}

void snake_render(SDL_Renderer* renderer, unsigned int size, SDL_Rect* rect)
{
	for (register int unsigned i = 0 ; i < size ; i++)
	{
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
		SDL_RenderFillRect(renderer, &rect[i]);
	}
}

