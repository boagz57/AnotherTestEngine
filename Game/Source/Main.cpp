/*TODO: Turn off exceptions (for speed purposes):	

		- https://stackoverflow.com/questions/553103/can-i-disable-exceptions-in-stl 

	and when handling std stl errors without exceptions:

		- https://stackoverflow.com/questions/3870435/handling-stl-errors-without-exceptions

	and make sure no exception based library is used. 
*/

#include <SDL.h>
#include "GameEngine\Graphics\RenderSystem.h"
#include "GameEngine\Graphics\ShaderProgram.h"
#include "GameEngine\Graphics\Window.h"
#include "GameEngine\Scene.h"
#include "GameEngine\Graphics\Sprite.h"
#include "GameEngine\Fighter.h"
#include "GameEngine\Timing\Timing.h"
#include "GameEngine\InputSystem.h"

int main(int agrc, char** argv)
{
	Blz::Window window;
	Blz::Graphics::ShaderProgram colorShaderProgram;
	Scene scene;

	window.Initialize();
	colorShaderProgram.Init("Source/GameEngine/Shaders/VertexShader.glsl", "Source/GameEngine/Shaders/FragmentShader.glsl");
	colorShaderProgram.Compile();
	colorShaderProgram.AddAttribute("vertexPosition");
	colorShaderProgram.AddAttribute("textCoord");
	colorShaderProgram.Link();
	colorShaderProgram.Bind();

	Fighter* player1 = scene.CreateFighter("CharImage.png", 100, 0);
	Fighter* player2 = scene.CreateFighter("CharImage.png", 900, 0);

	//Initialize systems
	Blz::Graphics::RenderSystem::Init(scene);

	//Game loop
	while (true)
	{

		Blz::InputSystem::ProcessInput(scene);

		//GameLogic


		window.ClearBuffers();

		Blz::Graphics::RenderSystem::Update(scene, colorShaderProgram);

		window.SwapBuffers();

		Blz::Timing::CalculateAndDisplayFPS();
	}

	return 0;
}
