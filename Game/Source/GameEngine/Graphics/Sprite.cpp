#include <cstddef> //For offsetof function below
#include <GL/glew.h>
#include <GLM/glm.hpp>
#include "Sprite.h"
#include "GLTexture.h"
#include "../ErrorContext.h"
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

	Blz::Graphics::GLTexture texture(imageFilePath);

	this->texture = texture;

	//TODO: switch to glm::vec3 instead of custom Vector3D class???
	vertexData.at(0) = Vector3D{ this->x + this->width, this->y + this->height, 0.0f };
	vertexData.at(1) = Vector3D{ this->x, this->y + height, 0.0f };
	vertexData.at(2) = Vector3D{ this->x, this->y, 0.0f };
	vertexData.at(3) = Vector3D{ this->x, this->y, 0.0f };
	vertexData.at(4) = Vector3D{ this->x + this->width, this->y, 0.0f };
	vertexData.at(5) = Vector3D{ this->x + this->width, this->y + this->height, 0.0f };

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
}
