#include <cstddef>
#include "Sprite.h"
#include "ImageHandling.h"
#include "Vector3D.h"
#include "GL/glew.h"

Sprite::Sprite()
{
	vboID = 0;
}

Sprite::~Sprite()
{
	//Clean up sprite buffers on GPU when done with sprite
	if (vboID != 0)
		glDeleteBuffers(1, &vboID);
}

void Sprite::Init(float x, float y, float width, float height, Blz::string imageFilePath)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	if (vboID == 0)
		glGenBuffers(1, &vboID);

	texture = Blz::OpenGL::LoadImage(imageFilePath);

	Vector3D vertexData[6]{
		Vector3D {x + width, y + height, 1.0f},
		Vector3D {x, y + height, 1.0f },
		Vector3D {x, y, 1.0f},
		Vector3D {x, y, 1.0f},
		Vector3D {x + width, y, 1.0f},
		Vector3D {x + width, y + height, 1.0f},
	};

	for (int i = 0; i < 6; ++i)
	{
		vertexData[i].color.r = 0;
		vertexData[i].color.g = 155;
		vertexData[i].color.b = 200;
	};

	vertexData[0].setUV(1.0f, 1.0f);
	vertexData[1].setUV(0.0f, 1.0f);
	vertexData[2].setUV(0.0f, 0.0f);
	vertexData[3].setUV(0.0f, 0.0f);
	vertexData[4].setUV(1.0f, 0.0f);
	vertexData[5].setUV(1.0f, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::Draw()
{
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, position));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, textCoordinate));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
