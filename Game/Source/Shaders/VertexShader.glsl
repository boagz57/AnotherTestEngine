#version 430

in vec2 vertexPosition;
in vec2 textCoord;
in vec4 color;

out vec2 TextureCoord;
out vec4 Color;

void main()
{
	vec4 position = vec4(vertexPosition, 0.0f, 1.0f);
	gl_Position = position;
	TextureCoord = textCoord;
	Color = color;
};