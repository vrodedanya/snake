#pragma once
#include <SDL2/SDL.h>

class Snake
{
public:
	Snake(SDL_Renderer* renderer, int x, int y, unsigned int width, unsigned int height, int range);

	~Snake();

	bool eat_apple(const SDL_Rect& apple);

	bool check();

	bool isSnake(const SDL_Rect& apple);

	SDL_Rect* get_snake()
	{
		return rect;
	}

	unsigned int get_size()
	{
		return size;
	}

	void move();

	void render();

	virtual void motion(const SDL_Rect& apple);

protected:

	SDL_Renderer* renderer;
	SDL_Rect* rect;
	SDL_Point dir;

	unsigned int width;
	unsigned int height;
	unsigned int size;
	int range;
};

class Player : public Snake
{
public:
	// call Snake constructor
	using Snake::Snake;

	void motion(SDL_Event event);
};
