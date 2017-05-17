#include <vector>
#include "SDL.h"
#include "GameEngine/Window.h"
#include "GameEngine\Sprite.h"
#include "GameEngine\ImageHandling.h"
#include "GameEngine\ShaderProgram.h"
#include "STB_Img\stb_image.h"
#include "GameEngine/GLLogging.h"
#include "GL/glew.h"
#include <iostream>

Blz::Window window;
Sprite playerSprite;

std::vector<Sprite*> p_sprites;

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

	p_sprites.push_back(new Sprite());
	p_sprites.back()->Init(-1.0f, 0.0f, 1.0f, 1.0f, "CharImage.png");

	p_sprites.push_back(new Sprite());
	p_sprites.back()->Init(-1.0f, -1.0f, 1.0f, 1.0f, "CharImage.png");

	p_sprites.push_back(new Sprite());
	p_sprites.back()->Init(0.0f, -1.0f, 1.0f, 1.0f, "CharImage.png");

	GameState gamestate{ GameState::PLAY };

	SDL_Event evnt;

	Blz::OpenGL::ShaderProgram colorShaderProgram("Source/GameEngine/Shaders/VertexShader.glsl", "Source/GameEngine/Shaders/FragmentShader.glsl");

	colorShaderProgram.Compile();
	colorShaderProgram.AddAttribute("vertexPosition");
	colorShaderProgram.AddAttribute("textCoord");
	colorShaderProgram.Link();
	colorShaderProgram.Bind();

	GLuint uniformLocation = colorShaderProgram.GetUniformLocation("basicTexture");
	glUniform1i(uniformLocation, 0);

	//This function should only be run in debug or development builds as it can be very computationally
	//expensive 
	Blz::OpenGL::IsProgramValid(colorShaderProgram.programID);

	Blz::OpenGL::LogShaderProgramProperties(colorShaderProgram.programID);

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

		for (int i = 0; i < p_sprites.size(); ++i)
			p_sprites[i]->Draw();

		window.SwapBuffers();
	}

	return 0;
}
