#include "function.h"
#include <iostream>


void snake_move(const unsigned int& size, SDL_Rect* rect, const SDL_Point& dir, const unsigned int& range, const int& w, const int& h)
{
	SDL_Point buf, add_buf;
	buf.x = rect[0].x;
	buf.y = rect[0].y;
	rect[0].x += range * dir.x;
	if (rect[0].x >= w) rect[0].x = 0;
	else if (rect[0].x < 0) rect[0].x = w - rect[0].w;

	rect[0].y += range * dir.y;	
	if (rect[0].y >= h) rect[0].y = 0;
	else if (rect[0].y < 0) rect[0].y = h - rect[0].h;

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

bool eat_apple(unsigned int& size, SDL_Rect*& rect, const SDL_Rect& apple, const unsigned int& range)
{
	if (rect[0].x == apple.x && rect[0].y == apple.y)
	{
		size++;
		SDL_Rect* buf = new SDL_Rect[size];
		for(int i = 0 ; i < (size - 1) ; i++)
		{
			buf[i] = rect[i];
		}
		buf[size - 1].w = range;
		buf[size - 1].h = range;
		delete[] rect;
		rect = buf;
		return true;
	}
	return false;
}

bool snake_check(const unsigned int& size, const SDL_Rect* rect) 
{
	for(register int unsigned i = 1; i < size ; i++)
	{
		if (rect[0].x == rect[i].x && rect[0].y == rect[i].y) return false;
	}
	return true;
}

void snake_render(SDL_Renderer* renderer, const unsigned int& size, const SDL_Rect* rect)
{
	for (register int unsigned i = 0 ; i < size ; i++)
	{
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
		SDL_RenderFillRect(renderer, &rect[i]);
	}
}

