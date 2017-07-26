#include <cstddef> //For offsetof function below
#include <GL/glew.h>
#include <GLM\detail\type_vec2.hpp>
#include <GLM\detail\type_vec3.hpp>
#include <math.h>
#include "Sprite.h"
#include "GLTexture.h"
#include "../ErrorContext.h"
#include "../ErrorHandling.h"
#include "../Vector3D.h"

//TODO: Remove all opengl code from here and have a separate renderer class that will take care of all rendering
/*
	Responsible for specifying the position and size of rectangle for which to draw the texture information
*/

Sprite::Sprite()
{
	vertexData.resize(6);
}

Sprite::~Sprite()
{
}

void Sprite::Init(int16 x, int16 y, uint16 width, uint16 height, Blz::string imageFilePath)
{
	Blz::Err::ErrorContext ec("When initializing sprite with image", imageFilePath);

	//casting to float since GLSL shader variables vec2,3,4 require vertex data to be in floats
	this->x = static_cast<sfloat>(x);
	this->y = static_cast<sfloat>(y);
	this->width = static_cast<sfloat>(width);
	this->height = static_cast<sfloat>(height);

	if (vboID == 0)
		glGenBuffers(1, &vboID);

	Blz::Graphics::GLTexture texture(imageFilePath);
	this->texture = texture;

	ERRASSERT(texture.id != 0, "Texture did not load properly!");

	//TODO: Need to be able to find center point of quadrilateral (since all sprites with be drawn onto a quad) so I can have sprites origin centered.
	this->vertexData.at(0).SetPosition(glm::vec3{ this->x + this->width, this->y + this->height, 0.0f });//Top right corner
	this->vertexData.at(1).SetPosition(glm::vec3{ this->x, this->y + height, 0.0f });//Top left corner
	this->vertexData.at(2).SetPosition(glm::vec3{ this->x, this->y, 0.0f });//Bottom left corner
	this->vertexData.at(3).SetPosition(glm::vec3{ this->x, this->y, 0.0f });//Bottom left corner
	this->vertexData.at(4).SetPosition(glm::vec3{ this->x + this->width, this->y, 0.0f });//Bottom right corner
	this->vertexData.at(5).SetPosition(glm::vec3{ this->x + this->width, this->y + this->height, 0.0f });//Top right corner

	this->vertexData.at(0).SetUV(glm::vec2{ 1.0f, 1.0f });
	this->vertexData.at(1).SetUV(glm::vec2{ 0.0f, 1.0f });
	this->vertexData.at(2).SetUV(glm::vec2{ 0.0f, 0.0f });
	this->vertexData.at(3).SetUV(glm::vec2{ 0.0f, 0.0f });
	this->vertexData.at(4).SetUV(glm::vec2{ 1.0f, 0.0f });
	this->vertexData.at(5).SetUV(glm::vec2{ 1.0f, 1.0f });

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(Vector3D) * this->vertexData.size()), &this->vertexData.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, position));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)offsetof(Vector3D, textureCoordinates));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
