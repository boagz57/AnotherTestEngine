#pragma once
#include <GL/glew.h>
#include "GLTexture.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	void Init(int16 screenCoordinateX, int16 screenCoordinateY, uint16 imageWidth, uint16 imageHeight, Blz::string imageFilePath);

	void Draw();

private:
	float x = 0.0f;
	float y = 0.0f;
	float width = 0.0f;
	float height = 0.0f;

	GLuint vboID = 0;

	Blz::OpenGL::GLTexture texture;
};

