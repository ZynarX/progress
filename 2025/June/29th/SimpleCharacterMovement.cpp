#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL.h>

#define FIXED_TIME_STEP 1.0f / 60.0f
#define FRAME_DELAY 1000 / 60

struct Character
{
	float x = 50.0f;
	float y = 50.0f;
	float speed = 100.0f;
	float width = 50.0f;
	float height = 50.0f;
};

void handle_input(SDL_Event& event, bool& is_running, Character& character);
void update_game(float deltaTime, Character& character);
void render(SDL_Renderer* renderer, Character& character);

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow(
		"Lesson 6 Part 5",
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
	Character player;

	Uint32 previousTick = SDL_GetTicks();
	float accumulator = 0.0f;

	while (is_running)
	{
		while (SDL_PollEvent(&event))
		{
			handle_input(event, is_running, player);
		}

		Uint32 currentTick = SDL_GetTicks();
		float deltaTime = (currentTick - previousTick) / 1000.0f;
		previousTick = currentTick;

		accumulator += deltaTime;

		while (accumulator >= FIXED_TIME_STEP)
		{
			update_game(deltaTime, player);
			accumulator -= FIXED_TIME_STEP;
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		render(renderer, player);

		SDL_RenderPresent(renderer);

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

void handle_input(SDL_Event& event, bool& is_running, Character& character)
{
	if (event.type == SDL_QUIT)
	{
		is_running = false;
	}
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP)
		{
			character.y -= character.speed * FIXED_TIME_STEP;
		}
		if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN)
		{
			character.y += character.speed * FIXED_TIME_STEP;
		}
		if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)
		{
			character.x -= character.speed * FIXED_TIME_STEP;
		}
		if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)
		{
			character.x += character.speed * FIXED_TIME_STEP;
		}
	}
}

void update_game(float deltaTime, Character& character)
{
	// handle physics and stuff (not yet implemented)
}

void render(SDL_Renderer* renderer, Character& character)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	SDL_Rect player = { (int)character.x, (int)character.y, (int)character.width, (int)character.height };

	SDL_RenderFillRect(renderer, &player);
}
