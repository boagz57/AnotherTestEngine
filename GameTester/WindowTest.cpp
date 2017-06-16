#include <GL\glew.h>
#include <gtest\gtest.h>
#include "GameEngine\Window.h"

TEST(WindowClass, WindowInitialize_True)
{
	Blz::Window win;
	win.Initialize();
}