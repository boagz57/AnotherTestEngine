/*TODO: Turn off exceptions (for speed purposes):	

		- https://stackoverflow.com/questions/553103/can-i-disable-exceptions-in-stl 

	and when handling std stl errors without exceptions:

		- https://stackoverflow.com/questions/3870435/handling-stl-errors-without-exceptions

	and make sure no exception based library is used. 
*/

#include "Graphics\ShaderProgram.h"
#include "Graphics\Window.h"
#include "Vertex2D.h"
#include "Timing\Timing.h"
#include "Graphics\Texture.h"
#include "Graphics\OpenGL\OpenGL.h"
#include "Containers\Array.h"
#include <GL\glew.h>

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

		Blz::Graphics::Texture texture("CatFighter.png");

		Vertex2D vert1{};
		Vertex2D vert2{};
		Vertex2D vert3{};

		vert1.SetPosition(glm::vec2{ 0.0f, 0.0f });
		vert2.SetPosition(glm::vec2{ 0.5f, 0.0f });
		vert3.SetPosition(glm::vec2{ 0.2f, 0.5f });

		Blz::Array<Vertex2D, 3> vertices {vert1, vert2, vert3};

		GLuint vboID = 0;
		glGenBuffers(1, &vboID);

		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, (sizeof(Vertex2D) * vertices.size()), &vertices.front(), GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, position));

		glDrawArrays(GL_ARRAY_BUFFER, 0, 3);
		
		window.ClearBuffers();

		window.SwapBuffers();

		Blz::Timing::CalculateAndDisplayFPS();
	}

	return 0;
}
