#include "SDL/SDL.h"
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
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	//Clear window color when utilizing sdl renderer
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
	SDL_RenderFillRect(renderer, nullptr);

	GameState gamestate{ GameState::PLAY };

	SDL_Event evnt;

	while (gamestate != GameState::EXIT)
	{
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

		SDL_RenderClear(renderer);

		//Draw to buffer

		SDL_RenderPresent(renderer);
	}

	return 0;
}