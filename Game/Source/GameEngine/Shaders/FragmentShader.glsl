#version 430

in vec2 TextureCoord;
out vec4 daColor;

uniform sampler2D basicTexture;

void main()
{
	vec4 texel = texture(basicTexture, TextureCoord);
	daColor = texel;
};