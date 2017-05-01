#pragma once
#include "GL/glew.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	void Init(float x, float y, float width, float height);

	void Draw();

private:
	float x;
	float y;
	float width;
	float height;
	GLuint vboID;

};

