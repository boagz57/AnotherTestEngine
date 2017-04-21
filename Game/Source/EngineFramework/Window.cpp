#include "SDL.h"
#include "SDL_image.h"
#include "Window.h"

namespace Blz
{
	Window::Window()
	{
	}

	Window::~Window()
	{
	}

	void Window::Initialize()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error", "SDL did not initialize", nullptr);
			SDL_Quit();
		}

		//Not necessarily needed but can help with errors
		int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			LOG("SDL_image did not initialize properly. SDL image error: %s\n", IMG_GetError());
		}

		window = SDL_CreateWindow("Shadow Gods", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, 0);
		if (window == nullptr)
		{
			LOG("ERROR: SDL window failed to initialize! SDL error: %s\n", SDL_GetError());
			SDL_Quit();
		}
	}

	void Window::Shutdown()
	{
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
}