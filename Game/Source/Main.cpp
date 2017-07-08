/*TODO: Turn off exceptions (for speed purposes):	

		- https://stackoverflow.com/questions/553103/can-i-disable-exceptions-in-stl 

	and when handling std stl errors without exceptions:

		- https://stackoverflow.com/questions/3870435/handling-stl-errors-without-exceptions

	and make sure no exception based library is used. 
*/

#include <vector>
#include <SDL.h>
#include <GL/glew.h>
#include <Array>
#include "GameEngine/Camera2D.h"
#include "GameEngine\Graphics\Window.h"
#include "GameEngine\Sprite.h"
#include "GameEngine\Timing\Timing.h"
#include "GameEngine\Input.h"
#include "GameEngine\ImageHandling.h"
#include "GameEngine\Graphics\ShaderProgram.h"
#include "STB_Img\stb_image.h"
#include "GameEngine\ErrorHandling.h"
#include "GameEngine/Graphics\GLLogging.h"

Blz::Window window;
Sprite playerSprite;

std::vector<Sprite*> p_sprites;

enum class GameState
{
	PLAY,
	EXIT
};

Blz::Camera2D camera;

int main(int agrc, char** argv)
{
	window.Initialize();
	camera.Init(1024, 768);

	for (int16 i = 0; i < 1000; ++i)
	{
		p_sprites.push_back(new Sprite());
		p_sprites.back()->Init(0, 0, 200, 200, "CharImage.png");
	}

	GameState gamestate{ GameState::PLAY };

	SDL_Event evnt;

	Blz::Graphics::ShaderProgram colorShaderProgram("Source/GameEngine/Shaders/VertexShader.glsl", "Source/GameEngine/Shaders/FragmentShader.glsl");

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
	Blz::Graphics::IsProgramValid(colorShaderProgram.programID);

	Blz::Graphics::LogShaderProgramProperties(colorShaderProgram.programID);

	while (gamestate != GameState::EXIT)
	{
		//Process input
		while (SDL_PollEvent(&evnt))
		{
			switch (evnt.type)
			{
			case SDL_QUIT:
				gamestate = GameState::EXIT;

			case SDL_KEYDOWN:
				Blz::Input::pressKey(evnt.key.keysym.sym);
				break;

			case SDL_KEYUP:
				Blz::Input::releaseKey(evnt.key.keysym.sym);
				break;
			}
		}

		if(Blz::Input::IsKeyPressed(SDLK_w))	
			camera.SetPosition(camera.GetPosition() + glm::vec2(0.0f, 50.0f));
		else if (Blz::Input::IsKeyPressed(SDLK_s))
			camera.SetPosition(camera.GetPosition() + glm::vec2(0.0f, -50.0f));
		else if (Blz::Input::IsKeyPressed(SDLK_a))
			camera.SetPosition(camera.GetPosition() + glm::vec2(50.0f, 0.0f));
		else if (Blz::Input::IsKeyPressed(SDLK_d))
			camera.SetPosition(camera.GetPosition() + glm::vec2(-50.0f, 0.0f));
		else if (Blz::Input::IsKeyPressed(SDLK_q))
			camera.SetScale(camera.GetScale() + .1f);
		else if (Blz::Input::IsKeyPressed(SDLK_z))
			camera.SetScale(camera.GetScale() + -.1f);

		glm::mat4 transformMatrix = camera.GetTransformationMatrix();
		glUniformMatrix4fv(ProjectMatrixUniformLocation, 1, GL_FALSE, &(transformMatrix[0][0]));

		window.ClearBuffers();

		camera.Update();

		for (uint32 i = 0; i < p_sprites.size(); ++i)
			p_sprites[i]->Draw();

		window.SwapBuffers();

		Blz::Timing::CalculateAndDisplayFPS();
	}

	return 0;
}
