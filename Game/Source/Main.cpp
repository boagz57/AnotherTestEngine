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
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/glm.hpp>
#include "GameEngine/Camera2D.h"
#include "GameEngine\Graphics\Window.h"
#include "GameEngine\Graphics\Sprite.h"
#include "GameEngine\Timing\Timing.h"
#include "GameEngine\Input.h"
#include "GameEngine\Graphics\ShaderProgram.h"
#include "GameEngine\Graphics\Renderer.h"
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
	Blz::Graphics::Renderer renderer;
	Sprite sprite;
	sprite.Init(1024/2, 768/2, 200, 200, "CharImage.png");

	renderer.Init(sprite);

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

		glm::mat4 orthoProjection = glm::ortho(0.0f, static_cast<sfloat>(1024), 0.0f, static_cast<sfloat>(768));
		glm::mat4 transformationMatrix = glm::translate(orthoProjection, glm::vec3{0.0f, 0.0f, 0.0f });

		GLuint transformationMatrixUniformLocation = colorShaderProgram.GetUniformLocation("transformationMatrix");
		glUniformMatrix4fv(transformationMatrixUniformLocation, 1, GL_FALSE, &(transformationMatrix[0][0]));

		window.ClearBuffers();

		renderer.Draw();

		window.SwapBuffers();

		Blz::Timing::CalculateAndDisplayFPS();
	}

	return 0;
}
