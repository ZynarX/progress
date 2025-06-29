// AN SDL2 CODE PROGRESS
#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL.h>

#define RATE 60.0f / 1000.0f
#define FRAME_DELAY 1000 / 60

int main(int argc, char* agrv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow(
		"Exercise 1",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		500,
		500,
		SDL_WINDOW_SHOWN
	);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (!renderer)
	{
		std::cerr << "Cannot create renderer..." << std::endl;
		return - 1;
	}

	bool is_running = true;
	SDL_Event event;

	const int FRAME_COUNT = 10;
	int current_frame = 0;

	Uint32 lastTick = SDL_GetTicks();
	float accumulator = 0.0f;

	Uint8 r = 255, g = 255, b = 255;

	while (is_running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				std::cout << "Quitting program..." << std::endl;
				is_running = false;
			}
		}

		Uint32 currentTick = SDL_GetTicks();
		float deltaTime = (currentTick - lastTick) / 1000.0f;
		lastTick = currentTick;

		accumulator += deltaTime;

		while (accumulator >= RATE)
		{
			current_frame = (current_frame + 1) % FRAME_COUNT;
			accumulator -= RATE;
		}

		g = (current_frame * 10) % 255;
		b = (current_frame * 10) % 255;

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, r, g, b, 255);
		SDL_Rect rectangle = { 0, 0, 100, 100 };

		SDL_RenderFillRect(renderer, &rectangle);

		SDL_RenderPresent(renderer);

		if (SDL_GetTicks() - currentTick < FRAME_DELAY)
		{
			SDL_Delay(FRAME_DELAY - (SDL_GetTicks() - currentTick));
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
