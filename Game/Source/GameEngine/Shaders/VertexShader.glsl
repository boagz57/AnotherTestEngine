#version 430

in vec3 vertexPosition;
in vec2 textCoord;

out vec2 TextureCoord;

void main()
{
	gl_Position = vec4(vertexPosition, 1.0f);
	TextureCoord = textCoord;
};