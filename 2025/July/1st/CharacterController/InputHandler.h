#include <iostream>
#include <unordered_map>
#include <SDL.h>
#pragma once

class InputHandler
{
private:
	std::unordered_map<SDL_Scancode, bool> previousKeys;
	std::unordered_map<SDL_Scancode, bool> currentKeys;
public:
	void HandleInput(bool& is_running);
	
	bool IsKeyPressed(SDL_Scancode Key);
	bool IsKeyReleased(SDL_Scancode Key);
	bool IsKeyheld(SDL_Scancode Key);
};
