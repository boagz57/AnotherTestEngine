/*TODO: Turn off exceptions (for speed purposes):	

		- https://stackoverflow.com/questions/553103/can-i-disable-exceptions-in-stl 

	and when handling std stl errors without exceptions:

		- https://stackoverflow.com/questions/3870435/handling-stl-errors-without-exceptions

	and make sure no exception based library is used. 
*/

#include <vector>
#include <SDL.h>
#include "GameEngine\Graphics\Renderer.h"
#include "GameEngine\Graphics\Window.h"
#include "GameEngine\Scene.h"
#include "GameEngine\Fighter.h"
#include "GameEngine\Timing\Timing.h"
#include "GameEngine\Input.h"

int main(int agrc, char** argv)
{
	Blz::Graphics::Renderer renderer;
	Blz::Window window;
	Blz::Input input;
	Scene scene;

	window.Initialize();
	renderer.Init();

	Fighter* player1 = scene.CreateFighter();

	while (!input.IsKeyPressed(SDLK_ESCAPE))
	{
		input.ProcessInput(scene);

		//GameLogic
		if (player1->GetPosition().x > 0)
			LOG("ahahaha");

		window.ClearBuffers();

		renderer.Draw(scene);

		window.SwapBuffers();

		Blz::Timing::CalculateAndDisplayFPS();
	}

	return 0;
}
