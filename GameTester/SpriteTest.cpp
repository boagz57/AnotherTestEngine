#include "GL\glew.h"
#include "GameEngine\Window.h"
#include "GameEngine\Sprite.h"

TEST(SpriteClass, SpriteInitialize_True)
{
	Blz::Window win;
	win.Initialize();
	Sprite sprite;
	sprite.Init(23, 32, 100, 100, "../Game/CharImage.png");
}