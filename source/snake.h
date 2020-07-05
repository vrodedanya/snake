#pragma once
#include <SDL2/SDL.h>
#include <vector>

class Snake
{
public:
	Snake(SDL_Renderer* renderer, int x, int y, unsigned int width, unsigned int height, int range);

	~Snake();

	bool eat_apple(const SDL_Rect& apple);

	bool check(std::vector<Snake>& list);

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
