#version 430

layout(location=0) in vec3 vertexPosition;
layout(location=1) in vec2 textCoord;

out vec2 TextureCoord;

void main()
{
	gl_Position = vec4(vertexPosition, 1.0f);
	TextureCoord = textCoord;
};