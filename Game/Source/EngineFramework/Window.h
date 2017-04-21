#include "SDL.h"
#pragma once

/*
	Responsible for Creating and managing a window context as well as initializing and shutting down 
	third party systems.
*/

namespace Blz
{
	class Window
	{
	public:
		Window();
		~Window();
		Window(const Window& copy) = delete;
		void operator=(const Window& copy) = delete;

		void Initialize();
		void Shutdown();

		SDL_Window* window;
	};
}