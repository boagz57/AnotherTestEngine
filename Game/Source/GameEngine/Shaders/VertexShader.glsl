#version 430

in vec3 vertexPosition;
in vec3 vertexColor;

out vec3 theColor;

void main()
{
	gl_Position = vec4(vertexPosition, 1.0f);
	theColor = vertexColor;
};