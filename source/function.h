#pragma once
#include <SDL2/SDL.h>
class Snake
{
public:
	Snake(SDL_Renderer* renderer, unsigned int width, unsigned int height);

	~Snake();

	bool eat_apple(const SDL_Rect& apple);

	bool check();

	void move();

	void render();

	void motion(SDL_Event event);

private:
	SDL_Renderer* renderer;
	unsigned int width;
	unsigned int height;
	SDL_Rect* rect;
	unsigned int size;
	int range;
	SDL_Point dir;
};
