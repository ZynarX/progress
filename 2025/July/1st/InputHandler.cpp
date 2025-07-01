#define SDL_MAIN_HANDLED
#include <iostream>
#include <unordered_map>
#include <SDL.h>

constexpr float FIXED_TIME_STEP = 1.0f / 60.0f;
constexpr float FRAME_DELAY = 1000 / 60;

class InputHandler
{
private:
	std::unordered_map<SDL_Scancode, bool> currentKeys;
	std::unordered_map<SDL_Scancode, bool> previousKeys;

	bool previousMouseLeftPressed = false;
	bool currentMouseLeftPressed = false;

	bool previousMouseRightPressed = false;
	bool currentMouseRightPressed = false;

	int xMouse;
	int yMouse;
public:
	void update(bool& is_running)
	{
		SDL_Event event;

		previousKeys = currentKeys;
		currentKeys.clear();

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				is_running = false;
			}
			else if(event.type == SDL_KEYDOWN)
			{
				currentKeys[event.key.keysym.scancode] = true;
			}
			else if (event.type == SDL_KEYUP)
			{
				currentKeys[event.key.keysym.scancode] = false;
			}
		}

		int x, y;

		Uint32 buttons = SDL_GetMouseState(&x, &y);

		previousMouseLeftPressed = currentMouseLeftPressed;
		previousMouseRightPressed = currentMouseRightPressed;

		currentMouseLeftPressed = (buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0;
		currentMouseRightPressed = (buttons & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0;

		xMouse = x;
		yMouse = y;
	}

	bool IsKeyPressed(SDL_Scancode key)
	{
		return currentKeys[key] && !previousKeys[key];
	}
	bool IsKeyReleased(SDL_Scancode key)
	{
		return !currentKeys[key] && previousKeys[key];
	}

	bool IsLeftMousePressed()
	{
		return currentMouseLeftPressed && !previousMouseLeftPressed;
	}
	bool IsLeftMouseReleased()
	{
		return !currentMouseLeftPressed && previousMouseLeftPressed;
	}

	bool IsRightMousePressed()
	{
		return currentMouseRightPressed && !previousMouseRightPressed;
	}
	bool IsRightMouseReleased()
	{
		return !currentMouseRightPressed && previousMouseRightPressed;
	}
};

struct Character
{
	float xPos = 10.0f;
	float yPos = 10.0f;
	const float SPEED = 150.0f;
	int WIDTH = 100;
	int HEIGHT = 100;
};

void render(SDL_Renderer* renderer, Character& player);


int main(int argc, char* agrv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow(
		"Project 2",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800,
		600,
		SDL_WINDOW_SHOWN
	);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (!renderer)
	{
		std::cerr << "Couldn't create renderer..." << std::endl;
		return -1;
	}

	bool is_running = true;
	InputHandler handler;

	Uint32 previousTick = SDL_GetTicks();
	float accumulator = 0.0f;

	Character player;

	while (is_running)
	{
		handler.update(is_running);

		Uint32 currentTick = SDL_GetTicks();
		float deltaTime = (currentTick - previousTick) / 1000.0f;
		previousTick = currentTick;

		accumulator += deltaTime;

		while (accumulator >= FIXED_TIME_STEP)
		{
			if (handler.IsKeyPressed(SDL_SCANCODE_W))
			{
				player.yPos -= player.SPEED * deltaTime;
			}
			if (handler.IsKeyPressed(SDL_SCANCODE_S))
			{
				player.yPos += player.SPEED * deltaTime;
			}
			if (handler.IsKeyPressed(SDL_SCANCODE_D))
			{
				player.xPos += player.SPEED * deltaTime;
			}
			if (handler.IsKeyPressed(SDL_SCANCODE_A))
			{
				player.xPos -= player.SPEED * deltaTime;
			}

			accumulator -= FIXED_TIME_STEP;
		}

		render(renderer, player);

		Uint32 lastTick = SDL_GetTicks();

		if (lastTick - currentTick < FRAME_DELAY)
		{
			SDL_Delay(FRAME_DELAY - (lastTick - currentTick));
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}

void render(SDL_Renderer* renderer, Character& player)
{
	SDL_SetRenderDrawColor(renderer, 200, 200, 255, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 155, 155, 255);
	SDL_Rect playerRect = { player.xPos, player.yPos, player.WIDTH, player.HEIGHT };

	SDL_RenderFillRect(renderer, &playerRect);

	SDL_RenderPresent(renderer);
}
