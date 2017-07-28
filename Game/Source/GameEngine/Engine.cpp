#include "Engine.h"
#include "Timing/Timing.h"
#include "Input.h"
#include "Graphics/Window.h"

Engine::Engine() 
{
}

Engine::~Engine()
{
}

void Engine::Init()
{
	window.Initialize();
	renderer.Init();
}

void Engine::GameLoop(Scene& scene, Game& game)
{
	Blz::Input input;

	while (!input.IsKeyPressed(SDLK_ESCAPE))
	{
		input.ProcessInput(scene);

		game.GameLogic(scene);

		window.ClearBuffers();

		renderer.Draw(scene);

		window.SwapBuffers();

		Blz::Timing::CalculateAndDisplayFPS();
	}
}
