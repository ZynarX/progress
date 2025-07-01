#include <iostream>
#include "InputHandler.h"

void InputHandler::HandleInput(bool& is_running)
{
	SDL_Event event;

	this->previousKeys = this->currentKeys;
	this->currentKeys.clear();

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			std::cout << "Quitting program..." << std::endl;
			is_running = false;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			this->currentKeys[event.key.keysym.scancode] = true;
		}
		else if (event.type == SDL_KEYUP)
		{
			this->currentKeys[event.key.keysym.scancode] = false;
		}
	}
}

bool InputHandler::IsKeyPressed(SDL_Scancode Key)
{
	return this->currentKeys[Key] && !this->previousKeys[Key];
}
bool InputHandler::IsKeyReleased(SDL_Scancode Key)
{
	return !this->currentKeys[Key] && this->previousKeys[Key];
}
bool InputHandler::IsKeyheld(SDL_Scancode Key)
{
	return this->currentKeys[Key];
}
