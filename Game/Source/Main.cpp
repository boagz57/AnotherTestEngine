#include <vector>
#include <iostream>
#include <SDL.h>
#include <GL/glew.h>
#include "GameEngine/Camera2D.h"
#include "GameEngine/Window.h"
#include "GameEngine\Sprite.h"
#include "GameEngine\ImageHandling.h"
#include "GameEngine\ShaderProgram.h"
#include "STB_Img\stb_image.h"
#include "GameEngine/GLLogging.h"

Blz::Window window;
Sprite playerSprite;

std::vector<Sprite*> p_sprites;

enum class GameState
{
	PLAY,
	EXIT
};

const uint32 maxFPS = 60;

Blz::Camera2D camera;

void CalculateFPS()
{
	static uint32 FPS;
	static uint32 frameTime;
	static int32 currentFrame = 0;

	static const int32 c_numSamples = 10;
	static uint32 frameTimes[c_numSamples];

	static uint32 previousTicks = SDL_GetTicks();

	uint32 currentTicks = SDL_GetTicks();

	frameTime = currentTicks - previousTicks;
	frameTimes[currentFrame % c_numSamples] = frameTime;

	previousTicks = currentTicks;

	uint32 count;

	currentFrame++;

	if (currentFrame < c_numSamples)
	{
		count = currentFrame; 
	}
	else
	{
		count = c_numSamples;
	}
	
	sfloat frameTimeAverage = 0;
	for (int32 i = 0; i < count; ++i)
	{
		frameTimeAverage += frameTimes[i];
	}

	frameTimeAverage /= count;

	if (frameTimeAverage > 0)
	{
		FPS = 1000 / frameTimeAverage;
	}
	else
	{
		FPS = 60.0f;
	}

	LOG("%i\n", FPS);
}

int main(int agrc, char** argv)
{
	window.Initialize();
	camera.Init(1024, 768);

	p_sprites.push_back(new Sprite());
	p_sprites.back()->Init(0, 0, 1024/2, 1024/2, "CharImage.png");

	p_sprites.push_back(new Sprite());
	p_sprites.back()->Init(1024/2, 0, 1024/2, 1024/2, "CharImage.png");

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

	GLuint ProjectMatrixUniformLocation = colorShaderProgram.GetUniformLocation("projectionMatrix");
	glm::mat4 transformMatrix = camera.GetTransformationMatrix();
	glUniformMatrix4fv(ProjectMatrixUniformLocation, 1, GL_FALSE, &(transformMatrix[0][0]));

	//This function should only be run in debug or development builds as it can be very computationally
	//expensive 
	Blz::OpenGL::IsProgramValid(colorShaderProgram.programID);

	Blz::OpenGL::LogShaderProgramProperties(colorShaderProgram.programID);

	while (gamestate != GameState::EXIT)
	{
		uint32 startTime = SDL_GetTicks();

		//Game Logic Update
		while (SDL_PollEvent(&evnt))
		{
			switch (evnt.type)
			{
			case SDL_QUIT:
				gamestate = GameState::EXIT;

			case SDL_KEYDOWN:
				switch (evnt.key.keysym.sym)
				{
				case SDLK_w:
					camera.SetPosition(camera.GetPosition() + glm::vec2(0.0f, 50.0f));
					break;

				case SDLK_s:
					camera.SetPosition(camera.GetPosition() + glm::vec2(0.0f, -50.0f));
					break;

				case SDLK_a:
					camera.SetPosition(camera.GetPosition() + glm::vec2(50.0f, 0.0f));
					break;

				case SDLK_d:
					camera.SetPosition(camera.GetPosition() + glm::vec2(-50.0f, 0.0f));
					break;

				case SDLK_q:
					camera.SetScale(camera.GetScale() + .1f);
					break;

				case SDLK_z:
					camera.SetScale(camera.GetScale() + -.1f);
					break;

				default:
					break;
				}

			default:
				break;
			}
		}

		glm::mat4 transformMatrix = camera.GetTransformationMatrix();
		glUniformMatrix4fv(ProjectMatrixUniformLocation, 1, GL_FALSE, &(transformMatrix[0][0]));

		window.ClearBuffers();

		camera.Update();

		for (uint32 i = 0; i < p_sprites.size(); ++i)
			p_sprites[i]->Draw();

		window.SwapBuffers();

		CalculateFPS();

		uint32 currentTime = SDL_GetTicks() - startTime;

		if (1000 / maxFPS > currentTime)
		{
			SDL_Delay(1000 / (maxFPS - currentTime));
		}
	}

	return 0;
}
