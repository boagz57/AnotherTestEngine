#include <cstddef> //For offsetof function below
#include <GL/glew.h>
#include <GLM\detail\type_vec2.hpp>
#include <GLM\detail\type_vec3.hpp>
#include <math.h>
#include "Sprite.h"
#include "../Graphics/Texture.h"
#include "../ErrorContext.h"
#include "../ErrorHandling.h"
#include "../Vector3D.h"

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


	Blz::Graphics::Texture texture(imageFilePath);
	this->texture = texture;

	ERRASSERT(texture.id != 0, "Texture did not load properly!");

	sfloat halfWidth = this->width / 2;

	//Setting sprite origin at bottom middle of image by subtracting half width 
	this->vertexData.at(0).SetPosition(glm::vec3{ this->x + (this->width - halfWidth), this->y + this->height, 0.0f });//Top right corner
	this->vertexData.at(1).SetPosition(glm::vec3{ this->x - halfWidth, this->y + height, 0.0f });//Top left corner
	this->vertexData.at(2).SetPosition(glm::vec3{ this->x - halfWidth, this->y, 0.0f });//Bottom left corner
	this->vertexData.at(3).SetPosition(glm::vec3{ this->x - halfWidth, this->y, 0.0f });//Bottom left corner
	this->vertexData.at(4).SetPosition(glm::vec3{ this->x + (this->width - halfWidth), this->y, 0.0f });//Bottom right corner
	this->vertexData.at(5).SetPosition(glm::vec3{ this->x + (this->width - halfWidth), this->y + this->height, 0.0f });//Top right corner

	this->vertexData.at(0).SetUV(glm::vec2{ 1.0f, 1.0f });
	this->vertexData.at(1).SetUV(glm::vec2{ 0.0f, 1.0f });
	this->vertexData.at(2).SetUV(glm::vec2{ 0.0f, 0.0f });
	this->vertexData.at(3).SetUV(glm::vec2{ 0.0f, 0.0f });
	this->vertexData.at(4).SetUV(glm::vec2{ 1.0f, 0.0f });
	this->vertexData.at(5).SetUV(glm::vec2{ 1.0f, 1.0f });
}
