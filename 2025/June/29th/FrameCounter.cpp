#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL.h>

#define RATE 60.0f / 1000.0f
#define FRAME_RATE 16

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow(
		"Exercise 3",
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

	const int FRAMES = 10;
	int current_frame = 0;

	float accumulator = 0.0f;

	Uint32 lastTick = SDL_GetTicks();

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
			std::cout << "Current Frame: " << current_frame << std::endl;
			current_frame = (current_frame + 1) % FRAMES;
			accumulator -= RATE;
		}

		SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
		SDL_RenderClear(renderer);

		SDL_RenderPresent(renderer);

		Uint32 lastTick = SDL_GetTicks();

		if (float(lastTick - currentTick) < FRAME_RATE)
		{
			std::cout << "FPS: " << int(lastTick - currentTick) << std::endl;
			current_frame = 0;
			SDL_Delay(FRAME_RATE - (lastTick - currentTick));
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
