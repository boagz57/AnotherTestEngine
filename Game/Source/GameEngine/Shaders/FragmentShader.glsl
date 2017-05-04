#version 430

out vec4 daColor;
in vec3 theColor;

uniform sampler2D basicTexture;

void main()
{
	daColor = vec4(theColor, 1.0);
};