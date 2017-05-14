#include "SDL.h"
#include "GameEngine/Window.h"
#include "GameEngine\Sprite.h"
#include "GameEngine\ShaderProgram.h"
#include "STB_Img\stb_image.h"
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
	playerSprite.Init(-1.0f, -1.0f, 2.0f, 2.0f);
	
	GameState gamestate{ GameState::PLAY };

	SDL_Event evnt;

	int32 x, y, currentChannels;
	int32 forceChannels = 4;
	uchar8* imageData = 0;
	imageData = stbi_load("CharImage.png", &x, &y, &currentChannels, forceChannels);

	if (imageData == nullptr)
	{
		LOG("ERROR: Could not load image file!");
	};

	Blz::OpenGL::ShaderProgram colorShaderProgram;
	colorShaderProgram.Compile();
	colorShaderProgram.Link();
	colorShaderProgram.Bind();

	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	GLuint uniformLocation = glGetUniformLocation(colorShaderProgram.programID, "basicTexture");
	glUniform1i(uniformLocation, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	LOG("%i", glGetError());

	//This function should only be run in debug or development builds as it can be very computationally
	//expensive 
	Blz::OpenGL::IsProgramValid(colorShaderProgram.programID);

	Blz::OpenGL::LogShaderProgramProperties(colorShaderProgram.programID);


	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

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
