#include "snake.h"
#include <iostream>

Snake::Snake(SDL_Renderer* renderer, int x, int y, unsigned int width, unsigned int height, int range)
{
	this->renderer = renderer;
	this->width = width;
	this->height = height;
	this->range = range;
	isMotion = false;
	size = 3;
	rect = new SDL_Rect[size];
	for (int i = 0 ; i < size ; i++)
	{
		rect[i].h = range;
		rect[i].w = range;
		rect[i].x =  -i * range + x;
		rect[i].y = y;
	}
	dir = {1, 0};
}
Snake::~Snake()
{
	delete[] rect;
}

bool Snake::isSnake(const SDL_Rect& apple)
{
	for (int i = 0 ; i < size ; i++)
	{
		if (apple.x == rect[i].x && apple.y == rect[i].y) return true;
	}
	return false;
}

void Snake::motion(const SDL_Rect& apple)
{
	if (apple.x > rect[0].x && rect[0].x + range != rect[1].x)
	{
		dir.x = 1;
		dir.y = 0;
	}
	else if (apple.x < rect[0].x && rect[0].x - range != rect[1].x)
	{
		dir.x = -1;
		dir.y = 0;
	}
	else
	{
		dir.x = 0;
		if (apple.y > rect[0].y && rect[0].y + range != rect[1].y) dir.y = 1;
		else if (rect[0].y - range != rect[1].y) dir.y = -1;
	}
}

void Snake::move()
{
	SDL_Point buf, add_buf;
	buf.x = rect[0].x;
	buf.y = rect[0].y;
	rect[0].x += range * dir.x;

	if (rect[0].x >= (int)width) rect[0].x = 0;
	else if (rect[0].x < 0) rect[0].x = width - rect[0].w;

	rect[0].y += range * dir.y;	
	if (rect[0].y >= (int)height) rect[0].y = 0;
	else if (rect[0].y < 0) rect[0].y = height - rect[0].h;

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

bool Snake::eat_apple(const SDL_Rect& apple)
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

bool Snake::check(std::vector<Snake>& list)
{
	for(register int unsigned i = 1; i < size ; i++)
	{
		if (rect[0].x == rect[i].x && rect[0].y == rect[i].y) 
		{
			return false;
		}
	}

	return true;
}

void Snake::render()
{
	for (register int unsigned i = 0 ; i < size ; i++)
	{
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
		if (i == 0) SDL_SetRenderDrawColor(renderer, 0, 170, 0, 0);
		SDL_RenderFillRect(renderer, &rect[i]);
	}
}
void Player::motion(SDL_Event event) 
{
	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_W] && rect[1].x != rect[0].x && rect[1].y != rect[0].y + (-1 * range))
	{
		dir.x = 0;
		dir.y = -1;
	}
	if (state[SDL_SCANCODE_A] && rect[1].y != rect[0].y && rect[1].x != rect[0].x + (-1 * range))
	{
		dir.x = -1;
		dir.y = 0;
	}
	if (state[SDL_SCANCODE_S] && rect[1].x != rect[0].x && rect[1].y != rect[0].y + range)
	{
		dir.x = 0;
		dir.y = 1;
	}
	if (state[SDL_SCANCODE_D] && rect[1].y != rect[0].y && rect[1].x != rect[0].x + range)
	{
		dir.x = 1;
		dir.y = 0;
	}
}
