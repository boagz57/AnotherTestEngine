#include <cstddef> //For offsetof function below
#include <GL/glew.h>
#include <GLM/glm.hpp>
#include "Sprite.h"
#include "ImageHandling.h"
#include "ErrorHandling.h"
#include "Vector3D.h"

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
	//Clean up sprite buffers on GPU when done with sprite
	if (vboID != 0)
		glDeleteBuffers(1, &vboID);
}

void Sprite::Init(int16 x, int16 y, uint16 width, uint16 height, Blz::string imageFilePath)
{
	//casting to float since GLSL shader variables vec2,3,4 require vertex data to be in floats
	static_cast<sfloat>(this->x) = x;
	static_cast<sfloat>(this->y) = y;
	static_cast<sfloat>(this->width) = width;
	static_cast<sfloat>(this->height) = height;

	if (vboID == 0)
		glGenBuffers(1, &vboID);

	texture = Blz::Graphics::LoadImageToGPU(imageFilePath);

	Vector3D vertexData[6]{			//TODO: switch to glm::vec3 instead of custom Vector3D class???
		Vector3D {this->x + this->width, this->y + this->height, 0.0f},
		Vector3D {this->x, this->y + height, 0.0f },
		Vector3D {this->x, this->y, 0.0f},
		Vector3D {this->x, this->y, 0.0f},
		Vector3D {this->x + this->width, this->y, 0.0f},
		Vector3D {this->x + this->width, this->y + this->height, 0.0f},
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
