/*TODO: Turn off exceptions (for speed purposes):	

		- https://stackoverflow.com/questions/553103/can-i-disable-exceptions-in-stl 

	and when handling std stl errors without exceptions:

		- https://stackoverflow.com/questions/3870435/handling-stl-errors-without-exceptions

	and make sure no exception based library is used. 
*/

#include <vector>
#include <Array>
#include "GameEngine\Graphics\Window.h"
#include "GameEngine\Graphics\Sprite.h"
#include "GameEngine\Timing\Timing.h"
#include "GameEngine\Input.h"
#include "GameEngine\Graphics\Renderer.h"
#include "GameEngine\ErrorHandling.h"

Blz::Window window;
Sprite playerSprite;

std::vector<Sprite*> p_sprites;

enum class GameState
{
	PLAY,
	EXIT
};

int main(int agrc, char** argv)
{
	window.Initialize();
	Blz::Graphics::Renderer renderer;
	Sprite sprite;
	sprite.Init(1024/2, 768/2, 200, 200, "CharImage.png");

	renderer.Init(sprite);

	GameState gamestate{ GameState::PLAY };

	SDL_Event evnt;
	
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

		window.ClearBuffers();

		renderer.Draw();

		window.SwapBuffers();

		Blz::Timing::CalculateAndDisplayFPS();
	}

	return 0;
}
