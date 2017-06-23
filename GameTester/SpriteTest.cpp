#include <gmock\gmock.h>
#include <gtest\gtest.h>
#include "GameEngine\Graphics\Window.h"
#include "GameEngine\Sprite.h"

TEST(SpriteClass, SpriteInitialize_True)
{
	Blz::Window win;
	win.Initialize();
	Sprite sprite;
	sprite.Init(23, 32, 100, 100, "../Game/CharImage.png");
}
