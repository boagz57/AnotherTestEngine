#pragma once
#include "GLTexture.h"
#include "GL/glew.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	void Init(float x, float y, float width, float height, Blz::string imageFilePath);

	void Draw();

private:
	float x;
	float y;
	float width;
	float height;

	GLuint vboID;

	Blz::OpenGL::GLTexture texture;
};

