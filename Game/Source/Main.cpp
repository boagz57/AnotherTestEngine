#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "Window.h"

enum class GameState
{
	PLAY,
	EXIT
};

int main(int agrc, char** argv)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error", "SDL did not initialize", nullptr);
		SDL_DestroyWindow(nullptr);
		SDL_Quit();
	}

	SDL_Window* window = SDL_CreateWindow("Shadow Gods", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, 0);
	if (window == nullptr)
	{
		LOG("ERROR: SDL window failed to initialize! SDL error: %s", SDL_GetError());
		SDL_Quit();
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		LOG("ERROR: SDL renderer failed to initialize! SDL error: %s", SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error", "SDL renderer did not initialize properly", window);

		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	//Not necessarily needed but can help with errors
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		LOG("SDL_image did not initialize properly. SDL image error: %s", IMG_GetError());
	}

	//Set background window color when utilizing sdl renderer
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
	SDL_RenderFillRect(renderer, nullptr);

	GameState gamestate{ GameState::PLAY };

	SDL_Event evnt;

	while (gamestate != GameState::EXIT)
	{
		unsigned int startTime = SDL_GetTicks();

		//Game Logic Update
		while (SDL_PollEvent(&evnt))
		{
			switch (evnt.type)
			{
			case SDL_QUIT:
				gamestate = GameState::EXIT;
				break;

			default:
				break;
			}
		}

		//Draw Game
		SDL_RenderClear(renderer);


		SDL_RenderPresent(renderer);

		unsigned int ms = startTime + 16.6 - SDL_GetTicks();
		SDL_Delay(ms);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}