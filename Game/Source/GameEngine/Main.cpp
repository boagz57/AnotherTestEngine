/*TODO: Turn off exceptions (for speed purposes):	

		- https://stackoverflow.com/questions/553103/can-i-disable-exceptions-in-stl 

	and when handling std stl errors without exceptions:

		- https://stackoverflow.com/questions/3870435/handling-stl-errors-without-exceptions

	and make sure no exception based library is used. 
*/

#include "Graphics\ShaderProgram.h"
#include "Graphics\Window.h"
#include "Timing\Timing.h"
#include <SDL.h>

int main(int agrc, char** argv)
{
	Blz::Graphics::Window window(1280, 720);
	Blz::Graphics::ShaderProgram colorShaderProgram;

	colorShaderProgram.Init("Source/GameEngine/Shaders/VertexShader.glsl", "Source/GameEngine/Shaders/FragmentShader.glsl");
	colorShaderProgram.Compile();
	colorShaderProgram.AddAttribute("vertexPosition");
	colorShaderProgram.AddAttribute("textCoord");
	colorShaderProgram.Link();
	colorShaderProgram.Bind();

	//Game loop
	while (true)
	{
		engineClock.UpdateTime();


		window.ClearBuffers();


		window.SwapBuffers();

		Blz::Timing::CalculateAndDisplayFPS();
	}

	return 0;
}
