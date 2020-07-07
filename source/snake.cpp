#include "snake.h"
#include <iostream>
unsigned int Snake::ID = 0;

Snake::Snake(SDL_Renderer* renderer, int r, int g, int b, int x, int y, unsigned int width, unsigned int height, int range)
{
	this->renderer = renderer;
	this->width = width;
	this->height = height;
	this->range = range;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = 0;


	snake_id = ID;
	ID++;
	size = 3;
	rect = new SDL_Rect[size];
	for (register unsigned int i = 0 ; i < size ; i++)
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

	bool isLock_x = false;
	bool isLock_y = false;
	for (register unsigned int i = 1 ; i < size ; i++)
	{
		if (rect[0].x + range * dir.x == rect[i].x && rect[0].y + range * dir.y == rect[i].y)
		{
			if (dir.y == 0 && isLock_y == false)
			{
				isLock_x = true;
				dir.x = 0;
				if (rect[i - 1].y < rect[i].y) dir.y = 1;
				else dir.y = -1;
			}
			else if (dir.x == 0 && isLock_x == false)
			{
				isLock_y = true;
				if (rect[i - 1].x < rect[i].x) dir.x = 1;
				else dir.x = -1;
				dir.y = 0;
			}
			else if (dir.y == 0 && isLock_y == true)
			{
				dir.x = -1;
				isLock_x = true;
			}
			else if (dir.x == 0 && isLock_x == true)
			{
				dir.y = -1;
				isLock_y = true;
			}
			else if (isLock_x == true && isLock_y == true)
			{
				exit(1);
			}
			i = 1;
		}
	}

}

void Snake::move()
{
	SDL_Point buf = {0, 0}, add_buf = {0, 0};
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
		for(register unsigned int i = 0 ; i < (size - 1) ; i++)
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

bool Snake::check_collision(const SDL_Rect& r)
{
	for (register unsigned int i = 0 ; i < size ; i++)
	{
		if (rect[i].x == r.x && rect[i].y == r.y) return true;
	}
	return false;
}

bool Snake::check(const std::vector<Snake*>& list)
{
	for(register int unsigned i = 1; i < size ; i++)
	{
		if (rect[0].x == rect[i].x && rect[0].y == rect[i].y) 
		{
			return false;
		}
	}

	for (Snake* i : list)
	{
		if (i->get_id() != this->snake_id)
		{
			for (register unsigned int j = 0 ; j < i->get_size() ; j++)
			{
				if (i->check_collision(rect[0])) return false;
			}
		}
	}

	return true;
}

void Snake::render()
{
	for (register int unsigned i = 0 ; i < size ; i++)
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0);
		if (i == 0) SDL_SetRenderDrawColor(renderer, color.r * 0.6, color.g * 0.6, color.b * 0.6, 0);
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
