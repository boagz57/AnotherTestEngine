#include <GL/glew.h>
#include <GLM\detail\type_vec2.hpp>
#include <GLM\detail\type_vec3.hpp>
#include "Sprite.h"

SpriteComponent::SpriteComponent()
{
	vertexData.resize(6);
}

void SpriteComponent::SetScreenTargetLocation(sfloat screenPositionX, sfloat screenPositionY, glm::ivec2 c_TextureTileDimensions)
{
	sfloat halfWidth = this->width / 2;

	tileDimensions = c_TextureTileDimensions;

	//Setting sprite origin at bottom middle of image by subtracting half width 
	this->vertexData.at(0).SetPosition(glm::vec3{ screenPositionX + (this->width - halfWidth), screenPositionY + this->height, 0.0f });//Top right corner
	this->vertexData.at(1).SetPosition(glm::vec3{ screenPositionX - halfWidth, screenPositionY + height, 0.0f });//Top left corner
	this->vertexData.at(2).SetPosition(glm::vec3{ screenPositionX - halfWidth, screenPositionY, 0.0f });//Bottom left corner
	this->vertexData.at(3).SetPosition(glm::vec3{ screenPositionX - halfWidth, screenPositionY, 0.0f });//Bottom left corner
	this->vertexData.at(4).SetPosition(glm::vec3{ screenPositionX + (this->width - halfWidth), screenPositionY, 0.0f });//Bottom right corner
	this->vertexData.at(5).SetPosition(glm::vec3{ screenPositionX + (this->width - halfWidth), screenPositionY + this->height, 0.0f });//Top right corner

	glm::vec4 uvs;

	uint16 xTile = index % tileDimensions.x;
	uint16 yTile = index / tileDimensions.x;

	uvs.x = xTile / static_cast<sfloat>(tileDimensions.x);
	uvs.y = yTile / static_cast<sfloat>(tileDimensions.y);
	uvs.w = 1.0f / tileDimensions.x;
	uvs.z = 1.0f / tileDimensions.y;

	this->vertexData.at(0).SetUV(glm::vec2{ uvs.x + uvs.w, uvs.y + uvs.z });
	this->vertexData.at(1).SetUV(glm::vec2{ uvs.x, uvs.y + uvs.z });
	this->vertexData.at(2).SetUV(glm::vec2{ uvs.x, uvs.y });
	this->vertexData.at(3).SetUV(glm::vec2{ uvs.x, uvs.y });
	this->vertexData.at(4).SetUV(glm::vec2{ uvs.x + uvs.w, uvs.y });
	this->vertexData.at(5).SetUV(glm::vec2{ uvs.x + uvs.w, uvs.y + uvs.z });

}

void SpriteComponent::SetWidthAndHeight(sfloat width, sfloat height)
{
	this->width = width;
	this->height = height;
}

void SpriteComponent::SetTextureID(GLuint id)
{
	this->textureID = id;
}

GLuint SpriteComponent::GetTextureID()
{
	return textureID;
}

Blz::SmallVector<Vector3D> SpriteComponent::GetVertexData()
{
	return vertexData;
}

void SpriteComponent::Update()
{
	glm::vec4 uvs;

	uint16 xTile = index % tileDimensions.x;
	uint16 yTile = index / tileDimensions.x;

	uvs.x = xTile / static_cast<sfloat>(tileDimensions.x);
	uvs.y = yTile / static_cast<sfloat>(tileDimensions.y);
	uvs.w = 1.0f / tileDimensions.x;
	uvs.z = 1.0f / tileDimensions.y;

	this->vertexData.at(0).SetUV(glm::vec2{ uvs.x + uvs.w, uvs.y + uvs.z });
	this->vertexData.at(1).SetUV(glm::vec2{ uvs.x, uvs.y + uvs.z });
	this->vertexData.at(2).SetUV(glm::vec2{ uvs.x, uvs.y });
	this->vertexData.at(3).SetUV(glm::vec2{ uvs.x, uvs.y });
	this->vertexData.at(4).SetUV(glm::vec2{ uvs.x + uvs.w, uvs.y });
	this->vertexData.at(5).SetUV(glm::vec2{ uvs.x + uvs.w, uvs.y + uvs.z });

	if (counter == 100)
	{
		index++;
		counter = 0;
	}

	counter++;
}
