#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL.h>

#define RATE 60.0f / 1000.0f
#define DELAY 16

int main(int agrc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow(
		"Exercise 2",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		500,
		500,
		SDL_WINDOW_SHOWN
	);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (!renderer)
	{
		std::cerr << "Couldn't create renderer..." << std::endl;
		return -1;
	}

	bool is_running = true;
	SDL_Event event;

	const int FRAME_COUNT = 10;
	int current_frame = 0;

	Uint32 lastTick = SDL_GetTicks();
	float accumulator = 0.0f;

	const int BASE_SIZE = 100;

	int xSize, ySize;

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

		int current_size = (current_frame * 5) + BASE_SIZE;

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

		SDL_Rect rectangle = { 0, 0, current_size, current_size };
		SDL_RenderFillRect(renderer, &rectangle);

		SDL_RenderPresent(renderer);

		if (SDL_GetTicks() - currentTick < DELAY)
		{
			SDL_Delay(DELAY - (SDL_GetTicks() - currentTick));
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
