#include "SDL.h"
#include "GameEngine/Window.h"
#include "GameEngine\Sprite.h"
#include "STB_Img\stb_image.h"
#include "GameEngine\ShaderProgram.h"
#include "GameEngine/GLLogging.h"
#include "GL/glew.h"
#include <iostream>

Blz::Window window;
Sprite playerSprite;

//For RenderCopy function. ScreenRectanlge captures entire screen while imageRectangle
//specifies the size you want to display the image
SDL_Rect screenRectangle{ 0, 0, 1024, 768 };
SDL_Rect imageRectangle{ 0, 0, 400, 100 };

enum class GameState
{
	PLAY,
	EXIT
};

int main(int agrc, char** argv)
{
	window.Initialize();
	playerSprite.Init(-1.0f, -1.0f, 1.0f, 1.0f);
	
	GameState gamestate{ GameState::PLAY };

	SDL_Event evnt;

	Blz::OpenGL::ShaderProgram colorShaderProgram;
	colorShaderProgram.Compile();
	colorShaderProgram.AddAttribute("vertexPosition");
	colorShaderProgram.AddAttribute("vertexColor");
	colorShaderProgram.Link();
	colorShaderProgram.Bind();

	Blz::OpenGL::LogTest(colorShaderProgram.programID);

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

		playerSprite.Draw();

		window.SwapBuffers();
	}

	return 0;
}
