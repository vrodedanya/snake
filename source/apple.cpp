#include "apple.h"

Apple::Apple(SDL_Renderer* renderer, unsigned int width, unsigned int height, unsigned int range)
{
	this->renderer = renderer;
	this->width = width;
	this->height = height;
	this->range = range;
	rect.w = range;
	rect.h = range;
}

bool Apple::isFree(const std::vector<Snake*>& list)
{
	for (Snake* item : list)
	{
		if (item->check_collision(rect)) return true;
	}
	return false;
}

void Apple::spawn(const std::vector<Snake*>& list)
{
	do
	{
		rect.x = rand()%(width / range) * range;
		rect.y = rand()%(height / range) * range;
	}
	while (isFree(list));
}

void Apple::render()
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0 ,0);
	SDL_RenderFillRect(renderer, &rect);
}
