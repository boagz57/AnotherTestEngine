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
	float x;
	float y;
	float width;
	float height;

	GLuint vboID;

	Blz::OpenGL::GLTexture texture;
};

