/*TODO: Turn off exceptions (for speed purposes):	

		- https://stackoverflow.com/questions/553103/can-i-disable-exceptions-in-stl 

	and when handling std stl errors without exceptions:

		- https://stackoverflow.com/questions/3870435/handling-stl-errors-without-exceptions

	and make sure no exception based library is used. 
*/

#include "Graphics\ShaderProgram.h"
#include "Graphics\Window.h"
#include "Scene.h"
#include "../Game.h"
#include "Fighter.h"
#include "Timing\Timing.h"
#include "Animation\AnimationEngine.h"
#include "Input\InputEngine.h"
#include "Graphics\GraphicsEngine.h"
#include "AI\AIEngine.h"
#include "Physics\PhysicsEngine.h"
#include <SDL.h>

Scene scene;

Blz::Graphics::Engine renderer;
Blz::Input::Engine input;
Blz::AI::Engine AI;
Blz::Animation::Engine animation;
Blz::Physics::Engine physics;

int main(int agrc, char** argv)
{
	Blz::Graphics::Window window(1920, 1080);
	Blz::Graphics::ShaderProgram colorShaderProgram;

	Game game;

	colorShaderProgram.Init("Source/GameEngine/Shaders/VertexShader.glsl", "Source/GameEngine/Shaders/FragmentShader.glsl");
	colorShaderProgram.Compile();
	colorShaderProgram.AddAttribute("vertexPosition");
	colorShaderProgram.AddAttribute("textCoord");
	colorShaderProgram.Link();
	colorShaderProgram.Bind();

	//Initialize systems
	engineClock.Init();
	game.Init();
	physics.Init(scene);
	renderer.Init(scene, window);
	animation.Init(scene);

	//Game loop
	while (true)
	{
		sfloat previousFrameDeltaTime = engineClock.UpdateTime();

		input.Update(scene);

		game.Update();

		physics.Update(scene, previousFrameDeltaTime);
		AI.Update(scene);
		animation.Update(scene);

		window.ClearBuffers();

		renderer.Update(scene, colorShaderProgram, window);

		window.SwapBuffers();

		Blz::Timing::CalculateAndDisplayFPS();
	}

	return 0;
}
