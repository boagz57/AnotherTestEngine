#include <GL\glew.h>
#include "GameEngine\Window.h"

TEST(WindowClass, WindowInitialize_True)
{
	Blz::Window win;
	win.Initialize();
}