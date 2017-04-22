#include "SDL.h"
#include "SDL_image.h"
#include "EngineFramework/Window.h"
#include "GL/glew.h"
#include <iostream>

SDL_Texture* texture;
SDL_Renderer* renderer;
Blz::Window window;

//For RenderCopy function. ScreenRectanlge captures entire screen while imageRectangle
//specifies the size you want to display the image
SDL_Rect screenRectangle{ 0, 0, 1024, 768 };
SDL_Rect imageRectangle{ 0, 0, 400, 100 };

enum class GameState
{
	PLAY,
	EXIT
};

void LoadImage(const char* imageFilePath);

int main(int agrc, char** argv)
{
	window.Initialize();

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

			default:
				break;
			}
		}

		window.ClearBuffers();


		window.SwapBuffers();
	}

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