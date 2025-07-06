#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL.h>

constexpr float FIXED_TIME_STEP = 1.0f / 60.0f;
constexpr float TIME_DELAY = 1000.0f / 60.0f;

bool CheckCollision(SDL_Rect* a, SDL_Rect* b);

int main(int agrc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow(
		"Bouncing Rectangle",
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
	
	SDL_Rect rectangle = { 100, 10, 50, 50 };
	SDL_Rect firstBorder = { 0, 0, 25, 500 };
	SDL_Rect secondBorder = { 475, 0, 25, 500 };
	SDL_Point velocity = { 500, 0 };

	Uint32 previousTick = SDL_GetTicks();
	float accumulator = 0.0f;

	while (is_running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				std::cout << "Quitting..." << std::endl;
				is_running = false;
			}
		}

		Uint32 currentTick = SDL_GetTicks();
		float deltaTime = (currentTick - previousTick) / 1000.0f;
		previousTick = currentTick;

		accumulator += deltaTime;

		while (accumulator >= FIXED_TIME_STEP)
		{
			int oldX = rectangle.x;

			rectangle.x += velocity.x * FIXED_TIME_STEP;

			if (CheckCollision(&rectangle, &firstBorder))
			{
				rectangle.x = oldX;
				velocity.x *= -1.01;
			}
			if (CheckCollision(&rectangle, &secondBorder))
			{
				rectangle.x = oldX;
				velocity.x *= -1.01;
			}

			accumulator -= FIXED_TIME_STEP;
		}

		SDL_SetRenderDrawColor(renderer, 155, 155, 255, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 155, 155, 255);
		SDL_RenderFillRect(renderer, &firstBorder);
		SDL_RenderFillRect(renderer, &secondBorder);

		SDL_SetRenderDrawColor(renderer, 155, 255, 155, 255);
		SDL_RenderFillRect(renderer, &rectangle);

		SDL_RenderPresent(renderer);

		Uint32 lastTick = SDL_GetTicks();
		float duration = lastTick - currentTick;

		if (duration < TIME_DELAY)
		{
			SDL_Delay(TIME_DELAY - duration);
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

bool CheckCollision(SDL_Rect* a, SDL_Rect* b)
{
	int aLeft = a->x;
	int aRight = a->x + a->w;
	int aTop = a->y;
	int aBottom = a->y + a->h;

	int bLeft = b->x;
	int bRight = b->x + b->w;
	int bTop = b->y;
	int bBottom = b->y + b->h;

	return ((aLeft < bRight && aRight > bLeft) && (aBottom > bTop && aTop < bBottom));
}
