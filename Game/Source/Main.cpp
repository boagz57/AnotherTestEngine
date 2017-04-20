#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "Window.h"

SDL_Texture* texture;
SDL_Renderer* renderer;

enum class GameState
{
	PLAY,
	EXIT
};

void LoadImage(const char* imageFilePath);

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
		LOG("ERROR: SDL window failed to initialize! SDL error: %s\n", SDL_GetError());
		SDL_Quit();
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		LOG("ERROR: SDL renderer failed to initialize! SDL error: %s\n", SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error", "SDL renderer did not initialize properly", window);

		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	//Not necessarily needed but can help with errors
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		LOG("SDL_image did not initialize properly. SDL image error: %s\n", IMG_GetError());
	}

	//Set background window color when utilizing sdl renderer
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
	SDL_RenderFillRect(renderer, nullptr);

	LoadImage("Goku.jpg");

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

		//For RenderCopy function. ScreenRectanlge captures entire screen while imageRectangle
		//specifies the size you want to display the image
		SDL_Rect screenRectangle{ 0, 0, 1024, 768 };
		SDL_Rect imageRectangle{ 0, 0, 400, 100 };

		//Draw Game
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, texture, &screenRectangle, &imageRectangle);

		SDL_RenderPresent(renderer);

		unsigned int ms = startTime + 16.6 - SDL_GetTicks();
		SDL_Delay(ms);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}

void LoadImage(const char* imageFilePath)
{
	//Load image into regular RAM memory. Surface means this in SDL
	SDL_Surface* surface = IMG_Load(imageFilePath);
	if (surface == nullptr)
	{
		LOG("Image did not load into RAM memory properly! SDL_Image error: %s\n", IMG_GetError());
	}

	//Send image down to GPU hardware memory. Texture means GPU stored image data
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == nullptr)
	{
		LOG("Image did not load into GPU memory properly! SDL_Image error: %s\n", IMG_GetError());
	}

	//Since we've loaded our image into memory we can now free the RAM memory of our
	//image data
	SDL_FreeSurface(surface);
}