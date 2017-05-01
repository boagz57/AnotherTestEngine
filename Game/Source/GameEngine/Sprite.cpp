#include <cstddef>
#include "Sprite.h"
#include "GameEngine/Vector3D.h"
#include "GL/glew.h"

Sprite::Sprite()
{
	vboID = 0;
}

Sprite::~Sprite()
{
}

void Sprite::Init(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	if (vboID == 0)
		glGenBuffers(1, &vboID);

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

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void Sprite::Draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, position));
	glVertexAttribPointer(1, 3, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vector3D), (void*)offsetof(Vector3D, color));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
