#pragma once
#include <SDL2/SDL.h>

class Snake
{
public:
	Snake(SDL_Renderer* renderer, unsigned int width, unsigned int height, int range);

	~Snake();

	bool eat_apple(const SDL_Rect& apple);

	bool check();

	bool isSnake(const SDL_Rect& apple);

	void move();

	void render();

	virtual void motion();

protected:
	SDL_Renderer* renderer;
	unsigned int width;
	unsigned int height;
	bool isMotion;
	SDL_Rect* rect;
	unsigned int size;
	int range;
	SDL_Point dir;
};

class Player : public Snake
{
	public:
	using Snake::Snake;

	void motion(SDL_Event event);
};
