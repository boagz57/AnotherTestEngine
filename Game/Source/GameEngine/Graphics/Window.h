#include <SDL.h>
#pragma once

namespace Blz::Graphics
{
	class Engine;

	class Window
	{
	public:
		Window() = delete;
		Window(uint16 width, uint16 height);
		~Window();
		Window(const Window& copy) = delete;
		void operator=(const Window& copy) = delete;

		auto ClearBuffers() -> void;
		auto SwapBuffers() -> void;

	private:
		friend class Engine;

		const uint16 width;
		const uint16 height;
		SDL_Window* p_window = nullptr;
		SDL_GLContext glContext = nullptr;
	};
}