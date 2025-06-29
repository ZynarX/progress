#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL.h>

#define FIXED_TIME_STEP 1.0f / 60.0f
#define FRAME_DELAY 1000 / 60

struct Player
{
	bool move_up           =  false;
	bool move_down         =  false;
	bool move_right        =  false;
	bool move_left         =  false;
	float xPos             =  50.0f; // Player starting X position
	float yPos             =  50.0f; // Player starting Y position
	const float MAX_SPEED  =  150.0f; // Player Max Speed
	int   WIDTH            =  75.0f; // Player rectangle width
	int   HEIGHT           =  75.0f; // Player rectangle height
};

struct Entity
{
	bool move_up           =  false;
	bool move_down         =  false;
	bool move_right        =  false;
	bool move_left         =  false;
	float xPos             =  50.0f; // Entity starting X position
	float yPos             =  150.0f; // Entity starting Y position
	const float MAX_SPEED  =  50.0f; // Entity Max Speed
	int   WIDTH            =  50.0f; // Entity rectangle width
	int   HEIGHT           =  50.0f; // Entity rectangle height
};

void handle_input(SDL_Event& event, bool& is_running, Player& player);
void handle_update(float deltaTime, Player& player, Entity& entity);
void handle_render(SDL_Renderer* renderer, Player& player, Entity& entity);

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow(
		"Project 0",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800,
		600,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (!renderer)
	{
		std::cerr << "Failed to create renderer..." << std::endl;
		return -1;
	}

	bool      is_running   = true;
	SDL_Event event;

	Uint32    previousTick = SDL_GetTicks();
	float     accumulator  = 0.0f;

	Player player;
	Entity entity;

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
			handle_update(deltaTime, player, entity);
			accumulator -= FIXED_TIME_STEP;
		}

		handle_render(renderer, player, entity);

		Uint32 finalTick = SDL_GetTicks();

		if (finalTick - currentTick < FRAME_DELAY)
		{
			SDL_Delay(FRAME_DELAY - (finalTick - currentTick));
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

void handle_input(SDL_Event& event, bool& is_running, Player& player)
{
	if (event.type == SDL_QUIT)
	{
		is_running = false;
	}
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP)
		{
			player.move_up = true;
		}
		if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN)
		{
			player.move_down = true;
		}
		if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)
		{
			player.move_right = true;
		}
		if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)
		{
			player.move_left = true;
		}
	}
	if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP)
		{
			player.move_up = false;
		}
		if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN)
		{
			player.move_down = false;
		}
		if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)
		{
			player.move_right = false;
		}
		if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)
		{
			player.move_left = false;
		}
	}
}

void handle_update(float deltaTime, Player& player, Entity& entity)
{
	if (player.move_up)
	{
		player.yPos -= player.MAX_SPEED * FIXED_TIME_STEP;
	}
	if (player.move_down)
	{
		player.yPos += player.MAX_SPEED * FIXED_TIME_STEP;
	}
	if (player.move_right)
	{
		player.xPos += player.MAX_SPEED * FIXED_TIME_STEP;
	}
	if (player.move_left)
	{
		player.xPos -= player.MAX_SPEED * FIXED_TIME_STEP;
	}

	if (entity.yPos > player.yPos)
	{
		entity.move_up = true;
	}
	else if (entity.yPos < player.yPos)
	{
		entity.move_down = true;
	}
	if (entity.xPos < player.xPos)
	{
		entity.move_right = true;
	}
	else if (entity.xPos > player.xPos)
	{
		entity.move_left = true;
	}

	if (entity.move_up)
	{
		entity.yPos -= entity.MAX_SPEED * FIXED_TIME_STEP;
	}
	if (entity.move_down)
	{
		entity.yPos += entity.MAX_SPEED * FIXED_TIME_STEP;
	}
	if (entity.move_right)
	{
		entity.xPos += entity.MAX_SPEED * FIXED_TIME_STEP;
	}
	if (entity.move_left)
	{
		entity.xPos -= entity.MAX_SPEED * FIXED_TIME_STEP;
	}

	entity.move_up = false;
	entity.move_down = false;
	entity.move_right = false;
	entity.move_left = false;
}

void handle_render(SDL_Renderer* renderer, Player& player, Entity& entity)
{
	SDL_SetRenderDrawColor(renderer, 225, 225, 225, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 0, 225, 0, 255);

	SDL_Rect playerRect = { (int)player.xPos, (int)player.yPos, (int)player.WIDTH, (int)player.HEIGHT };

	SDL_RenderFillRect(renderer, &playerRect);

	SDL_SetRenderDrawColor(renderer, 225, 0, 0, 255);

	SDL_Rect entityRect = { (int)entity.xPos, (int)entity.yPos, (int)entity.WIDTH, (int)entity.HEIGHT };

	SDL_RenderFillRect(renderer, &entityRect);

	SDL_RenderPresent(renderer);
}
