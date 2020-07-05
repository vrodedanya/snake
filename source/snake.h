#pragma once
#include <SDL2/SDL.h>
#include <vector>

class Snake
{
public:
	// Constructor
	Snake(SDL_Renderer* renderer, int r, int g, int b, int x, int y, unsigned int width, unsigned int height, int range);

	virtual	~Snake();
	
	// ID generator for all objects that created as Snake
	static unsigned int ID;

	// Check is snake head coords equal apple coords
	bool eat_apple(const SDL_Rect& apple);

	// Check entering snake's head coors in other snakes or itself
	bool check(const std::vector<Snake*>& list);

	// Move snake
	void move();

	// Draw snake
	void render();

	// Check entering rectangle to the snake
	bool check_collision(const SDL_Rect& r); 

	// Snake motion logic
	virtual void motion(const SDL_Rect& apple);

	SDL_Rect get_head(){return rect[0];}

	unsigned int get_size(){return size;}

	unsigned int get_id(){return snake_id;}
protected:
	SDL_Point dir;
	int range;
	SDL_Rect* rect; // Array with snake's coords
private:
	SDL_Renderer* renderer;
	SDL_Color color;

	unsigned int snake_id;

	unsigned int width; // Screen width
	unsigned int height; // Screen height
	unsigned int size; // Snake's size
};

class Player : public Snake
{
public:
	// call Snake constructor
	using Snake::Snake;

	// Player motion
	void motion(SDL_Event event); 
};
