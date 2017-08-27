#include <GL/glew.h>
#include <GLM\detail\type_vec2.hpp>
#include <GLM\detail\type_vec3.hpp>
#include "SpriteTileSheet.h"

SpriteTileSheetComponent::SpriteTileSheetComponent()
{
	vertexData.resize(6);
}

void SpriteTileSheetComponent::SetScreenTargetLocationAndTileDimensions(sfloat screenPositionX, sfloat screenPositionY, glm::ivec2 spriteSheetTileDimensions)
{
	tileDimensions = spriteSheetTileDimensions;

	sfloat halfWidth = this->width / 2;

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

void SpriteTileSheetComponent::SetWidthAndHeight(sfloat width, sfloat height)
{
	this->width = width;
	this->height = height;
}

void SpriteTileSheetComponent::SetTextureID(GLuint id)
{
	this->textureID = id;
}

GLuint SpriteTileSheetComponent::GetTextureID()
{
	return textureID;
}

Blz::SmallVector<Vector3D> SpriteTileSheetComponent::GetVertexData()
{
	return vertexData;
}

void SpriteTileSheetComponent::SetUVs(const uint16 startingIndex)
{
	glm::vec4 uvs;

	this->index = startingIndex;

	uint16 xTile = startingIndex % tileDimensions.x;
	uint16 yTile = startingIndex / tileDimensions.x;

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

uint16 const SpriteTileSheetComponent::CheckIndex() const
{
	return this->index;
}
