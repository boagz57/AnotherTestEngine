#version 430

out vec4 daColor;
in vec2 TextureCoord;

uniform sampler2D basicTexture;

void main()
{
	vec4 texel = texture(basicTexture, TextureCoord);
	daColor = texel;
};