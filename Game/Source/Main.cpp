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
#include "GameEngine\GameWorld\GameWorldManager.h"
#include "GameEngine\Graphics\RenderManager.h"
#include "GameEngine\AI\AIManager.h"
#include "GameEngine\Physics\PhysicsManager.h"

int main(int agrc, char** argv)
{
	Blz::Graphics::Window window(1280, 720);
	Blz::Graphics::ShaderProgram colorShaderProgram;
	Blz::Graphics::RenderManager Renderer;
	Blz::Input::InputManager Input;
	Blz::AI::AIManager AI;
	Blz::Physics::PhysicsManager Physics;
	Blz::GameWorld::GameWorldManager gameWolrd;
	Scene scene;

	colorShaderProgram.Init("Source/GameEngine/Shaders/VertexShader.glsl", "Source/GameEngine/Shaders/FragmentShader.glsl");
	colorShaderProgram.Compile();
	colorShaderProgram.AddAttribute("vertexPosition");
	colorShaderProgram.AddAttribute("textCoord");
	colorShaderProgram.Link();
	colorShaderProgram.Bind();

	auto* p_Enemy = scene.CreateAIFighter(80.0f, 45.0f);
	auto* p_Player = scene.CreatePlayerFighter(160.0f, 0.0f);

	//Initialize systems
	gameWolrd.Init(scene);
	Renderer.Init(scene, window);

	//Game loop
	while (true)
	{
		Input.Update(scene);

		Physics.Update(scene);
		AI.Update(scene);

		//GameLogic


		window.ClearBuffers();

		Renderer.Update(scene, colorShaderProgram);

		window.SwapBuffers();

		Blz::Timing::CalculateAndDisplayFPS();
	}

	return 0;
}
