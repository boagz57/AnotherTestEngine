/*TODO: Turn off exceptions (for speed purposes):	

		- https://stackoverflow.com/questions/553103/can-i-disable-exceptions-in-stl 

	and when handling std stl errors without exceptions:

		- https://stackoverflow.com/questions/3870435/handling-stl-errors-without-exceptions

	and make sure no exception based library is used. 
*/

#include <vector>
#include <Array>
#include <SDL.h>
#include "GameEngine\Graphics\Sprite.h"
#include "GameEngine\Engine.h"
#include "GameEngine\Scene.h"
#include "ShadowGodsGame.h"
#include "GameEngine\Fighter.h"
#include "GameEngine\Timing\Timing.h"
#include "GameEngine\Input.h"
#include "GameEngine\ErrorHandling.h"

int main(int agrc, char** argv)
{
	ShadowGodsGame myGame;
	Scene scene;
	Engine engine;
	engine.Init();

	Fighter player1("CharImage.png");

	scene.AddFighterToScene(player1);

	engine.GameLoop(scene, myGame);

	return 0;
}
