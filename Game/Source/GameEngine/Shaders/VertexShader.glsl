#version 430

in vec3 vertexPosition;
in vec2 textCoord;

out vec2 TextureCoord;

uniform mat4 projectionMatrix;

void main()
{
	vec4 position = vec4(vertexPosition, 1.0f);
	gl_Position = projectionMatrix * position;
	TextureCoord = textCoord;
};