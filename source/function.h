#pragma once
#include <SDL2/SDL.h>
bool eat_apple(unsigned int& size, SDL_Rect*& rect, const SDL_Rect& apple, const unsigned int& range);

bool snake_check(const unsigned int& size, const SDL_Rect* rect);

void snake_move(const unsigned int& size, SDL_Rect* rect, const SDL_Point& point, const unsigned int& range, const int& w, const int& h);

void snake_render(SDL_Renderer* renderer, const unsigned int& size, const SDL_Rect* rect);
