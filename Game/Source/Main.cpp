/*TODO: Turn off exceptions (for speed purposes):	

		- https://stackoverflow.com/questions/553103/can-i-disable-exceptions-in-stl 

	and when handling std stl errors without exceptions:

		- https://stackoverflow.com/questions/3870435/handling-stl-errors-without-exceptions

	and make sure no exception based library is used. 
*/

#include <vector>
#include <Array>
#include <SDL.h>
#include "GameEngine\Graphics\Window.h"
#include "GameEngine\Graphics\Sprite.h"
#include "GameEngine\Fighter.h"
#include "GameEngine\Timing\Timing.h"
#include "GameEngine\Input.h"
#include "GameEngine\Graphics\Renderer.h"
#include "GameEngine\ErrorHandling.h"

Blz::Window window;
Sprite playerSprite;

std::vector<Sprite*> p_sprites;

int main(int agrc, char** argv)
{
	window.Initialize();
	
	Blz::Graphics::Renderer renderer;

	//Player class, which inherits from fighter, will call a scene function within contructor adding fighter to scene in background
	//Player player1;
	//if (Player1.GetPosition().x > 0)
	//{   ..do something  };

	Fighter player1("CharImage.png");
	renderer.Init();

	Blz::Input input;

	while (!input.IsKeyPressed(SDLK_ESCAPE))
	{
		input.ProcessInput(player1);

		window.ClearBuffers();

		renderer.Draw(player1);

		window.SwapBuffers();

		Blz::Timing::CalculateAndDisplayFPS();
	}

	return 0;
}
