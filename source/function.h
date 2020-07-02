#pragma once
#include <SDL2/SDL.h>

bool snake_check(unsigned int size, SDL_Rect* rect);

void snake_move(unsigned int size, SDL_Rect* rect, SDL_Point& point, unsigned int& range);

void snake_render(SDL_Renderer* renderer,unsigned int size, SDL_Rect* rect);
