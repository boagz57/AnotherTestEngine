/*TODO: Turn off exceptions (for speed purposes):	

		- https://stackoverflow.com/questions/553103/can-i-disable-exceptions-in-stl 

	and when handling std stl errors without exceptions:

		- https://stackoverflow.com/questions/3870435/handling-stl-errors-without-exceptions

	and make sure no exception based library is used. 
*/

#include "GameEngine\Graphics\ShaderProgram.h"
#include "GameEngine\Graphics\Window.h"
#include "GameEngine\Scene.h"
#include "GameEngine\Fighter.h"
#include "GameEngine\Timing\Timing.h"
#include "GameEngine\Input\InputManager.h"
#include "GameEngine\Graphics\RenderManager.h"
#include "GameEngine\AI\AIManager.h"
#include "GameEngine\Physics\PhysicsManager.h"

int main(int agrc, char** argv)
{
	Blz::Window window;
	Blz::Graphics::ShaderProgram colorShaderProgram;
	Blz::Graphics::RenderManager Renderer;
	Blz::Input::InputManager Input;
	Blz::AI::AIManager AI;
	Blz::Physics::PhysicsManager Physics;
	Scene scene;

	window.Initialize();
	colorShaderProgram.Init("Source/GameEngine/Shaders/VertexShader.glsl", "Source/GameEngine/Shaders/FragmentShader.glsl");
	colorShaderProgram.Compile();
	colorShaderProgram.AddAttribute("vertexPosition");
	colorShaderProgram.AddAttribute("textCoord");
	colorShaderProgram.Link();
	colorShaderProgram.Bind();

	Fighter* enemy = scene.CreateAIFighter("CharImage.png", 900.0f, 0.0f);
	Fighter* player = scene.CreatePlayerFighter("CharImage.png", 0.0f, 0.0f);

	//Initialize systems
	Renderer.Init(scene);

	//Game loop
	while (true)
	{
		Input.ProcessInput(scene);

		Scene newScene = Physics.Update(scene);
		newScene = AI.Update(newScene);

		//GameLogic



		window.ClearBuffers();

		Renderer.Update(newScene, colorShaderProgram);

		window.SwapBuffers();

		Blz::Timing::CalculateAndDisplayFPS();
	}

	return 0;
}
