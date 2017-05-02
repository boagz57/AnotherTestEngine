#include "SDL.h"
#include "GL/glew.h"
#include "GLLogging.h"
#include "Window.h"

namespace Blz
{
	Window::Window()
	{
	}

	Window::~Window()
	{
		//In case window::Shutdown() function never gets called
		SDL_GL_DeleteContext(glContext);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	void Window::Initialize()
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error", "SDL did not initialize", nullptr);
			SDL_Quit();
		}

		//Attributes Need to be set before window creation
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		window = SDL_CreateWindow("Shadow Gods", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_OPENGL);
		if (window == nullptr)
		{
			LOG("ERROR: SDL window failed to initialize! SDL error: %s\n", SDL_GetError());
			SDL_Quit();
		}

		glContext = SDL_GL_CreateContext(window);

		//Turns on or off v-sync
		SDL_GL_SetSwapInterval(0);

		//Log current computer opengl version and capabilities
		OpenGL::RestartGLLogFile();
		OpenGL::LogToFile("OpenGL Version %s\n\n", glGetString(GL_VERSION));
		LOG("OpenGL Version %s", glGetString(GL_VERSION));
		OpenGL::LogCurrentGPUCapabilites();

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			LOG("ERROR: GLEW failed to initialize!");

			SDL_GL_DeleteContext(glContext);
			SDL_DestroyWindow(window);
			SDL_Quit();
		}

		//Sets the values that the depth and color buffers will be set to when glClear
		//is called
		glClearDepth(1.0);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}

	void Window::Shutdown()
	{
		SDL_GL_DeleteContext(glContext);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	void Window::ClearBuffers()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::SwapBuffers()
	{
		SDL_GL_SwapWindow(window);
	}
}