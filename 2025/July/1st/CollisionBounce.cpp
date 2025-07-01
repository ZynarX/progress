#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL.h>

constexpr float FIXED_TIME_STEP = 1.0f / 60.0f;
constexpr float FRAME_DELAY = 1000 / 60;

bool CheckCollision(SDL_Rect a, SDL_Rect b);

int main(int agrc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow(
		"Lesson 8 Part 3",
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
	SDL_Event event;

	SDL_Rect A = { 10, 10, 50, 50 };
	SDL_Point aVelocity = { 50, 0 };

	SDL_Rect B = { 300, 10, 75, 75 };

	Uint32 previousTick = SDL_GetTicks();
	float accumulator = 0.0f;

	while (is_running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				is_running = false;
			}
		}

		Uint32 currentTick = SDL_GetTicks();
		float deltaTime = (currentTick - previousTick) / 1000.0f;
		previousTick = currentTick;

		accumulator += deltaTime;


		while (accumulator >= FIXED_TIME_STEP)
		{
			A.x += aVelocity.x * deltaTime;

			if (CheckCollision(A, B))
			{
				aVelocity.x *= -1;
			}

			accumulator -= FIXED_TIME_STEP;
		}

		SDL_SetRenderDrawColor(renderer, 200, 200, 255, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 200, 200, 255);
		SDL_RenderFillRect(renderer, &A);

		SDL_SetRenderDrawColor(renderer, 200, 255, 200, 255);
		SDL_RenderFillRect(renderer, &B);

		SDL_RenderPresent(renderer);

		Uint32 lastTick = SDL_GetTicks();

		if (float(lastTick - currentTick) < FRAME_DELAY)
		{
			SDL_Delay(FRAME_DELAY - (lastTick - currentTick));
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

bool CheckCollision(SDL_Rect a, SDL_Rect b)
{
	int aLeft = a.x;
	int aRight = a.x + a.w;
	int aTop = a.y;
	int aBottom = a.y + a.h;

	int bLeft = b.x;
	int bRight = b.x + b.w;
	int bTop = b.y;
	int bBottom = b.y + b.h;

	return (aRight > bLeft && aLeft < bRight &&
		aBottom > bTop && aTop < bBottom);
}
