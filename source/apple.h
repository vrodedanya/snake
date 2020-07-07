#pragma once
#include "snake.h"

class Apple
{
public:
	Apple(SDL_Renderer* renderer, unsigned int width, unsigned int height, unsigned int range);

	void spawn(const std::vector<Snake*>& list); 

	void render();

	SDL_Rect get_rect(){return rect;}
private:
	SDL_Renderer* renderer;
	bool isFree(const std::vector<Snake*>& list);
	SDL_Rect rect;
	unsigned int width;
	unsigned int height;
	unsigned int range;
};
