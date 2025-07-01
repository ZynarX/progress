#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL.h>
#include "InputHandler.h"

constexpr float FIXED_TIME_STEP = 1.0f / 120.0f;
constexpr float FRAME_DELAY = 1000 / 120;

struct Character
{
	float xPos = 10.0f;
	float yPos = 10.0f;
	float MAX_SPEED = 250.0f;
	float VerticalVelocity = 0.0f;
	float HorizontalVelocity = 0.0f;
	float WIDTH = 100;
	float HEIGHT = 100;
};

void HandleControl(InputHandler& handler, float deltaTime, Character& character);
void Render(SDL_Renderer* renderer, Character& character);

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow(
		"Practice 3",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800,
		600,
		SDL_WINDOW_SHOWN
	);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (!renderer)
	{
		std::cout << "Cannot create renderer..." << std::endl;
		return -1;
	}

	bool is_running = true;
	Character player;
	InputHandler handler;

	Uint32 previousTick = SDL_GetTicks();
	float accumulator = 0.0f;

	while (is_running)
	{
		handler.HandleInput(is_running);

		Uint32 currentTick = SDL_GetTicks();
		float deltaTime = (currentTick - previousTick) / 1000.0f;
		previousTick = currentTick;

		accumulator += deltaTime;

		while (accumulator >= FIXED_TIME_STEP)
		{
			HandleControl(handler, deltaTime, player);
			accumulator -= FIXED_TIME_STEP;
		}

		Render(renderer, player);

		Uint32 lastTick = SDL_GetTicks();
		float delay = (float)(lastTick - currentTick);

		if (delay < FRAME_DELAY)
		{
			SDL_Delay(FRAME_DELAY - delay);
		}
	}
}

void HandleControl(InputHandler& handler, float deltaTime, Character& character)
{
	if (handler.IsKeyheld(SDL_SCANCODE_W))
	{
		character.VerticalVelocity = -character.MAX_SPEED;
	}
	if (handler.IsKeyheld(SDL_SCANCODE_S))
	{
		character.VerticalVelocity = character.MAX_SPEED;
	}
	if (handler.IsKeyheld(SDL_SCANCODE_D))
	{
		character.HorizontalVelocity = character.MAX_SPEED;
	}
	if (handler.IsKeyheld(SDL_SCANCODE_A))
	{
		character.HorizontalVelocity = -character.MAX_SPEED;
	}

	character.xPos += character.HorizontalVelocity * deltaTime;
	character.yPos += character.VerticalVelocity * deltaTime;

	character.HorizontalVelocity = 0.0f;
	character.VerticalVelocity = 0.0f;
}

void Render(SDL_Renderer* renderer, Character& character)
{
	SDL_SetRenderDrawColor(renderer, 200, 200, 255, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 200, 200, 255);
	SDL_Rect characterRectangle = { (int)character.xPos, (int)character.yPos, (int)character.WIDTH, (int)character.HEIGHT };

	SDL_RenderFillRect(renderer, &characterRectangle);

	SDL_RenderPresent(renderer);
}
