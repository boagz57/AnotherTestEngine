#include <SDL.h>
#pragma once

/*
	Responsible for Creating and managing an opengl window context as well as initializing and shutting down 
	third party systems.
*/

namespace Blz
{
	namespace Graphics
	{
		class RenderManager;

		class Window
		{
		public:
			Window(uint16 width, uint16 height);
			~Window();
			Window(const Window& copy) = default;
			void operator=(const Window& copy) = delete;

			void ClearBuffers();
			void SwapBuffers();

		private:
			friend class RenderManager;

			const uint16 width;
			const uint16 height;
			SDL_Window* p_window = nullptr;
			SDL_GLContext glContext = nullptr;
		};
	}
}