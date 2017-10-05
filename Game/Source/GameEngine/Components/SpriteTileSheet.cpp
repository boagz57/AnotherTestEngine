#include <GL/glew.h>
#include <GLM\detail\type_vec2.hpp>
#include <GLM\detail\type_vec3.hpp>
#include "Graphics\Texture.h"
#include "SpriteTileSheet.h"

namespace Comp
{
	void SpriteTileSheet::Init(const sfloat screenPositionX, const sfloat screenPositionY, const glm::ivec2 spriteSheetTileDimensions, 
						       uint16 scale /* = 1 */)
	{
		tileDimensions = spriteSheetTileDimensions;

		uint16 singleSpriteWidth = texture.GetWidth() / tileDimensions.x;
		uint16 singleSpriteHeight = texture.GetHeight() / tileDimensions.y;

		singleSpriteWidth *= scale;
		singleSpriteHeight *= scale;

		sfloat halfSpriteWidth = static_cast<sfloat>(singleSpriteWidth / 2);

		//Setting sprite origin at bottom middle of image by subtracting half width 
		this->vertexData.at(0).SetPosition(glm::vec3{ screenPositionX + halfSpriteWidth, screenPositionY + singleSpriteHeight, 0.0f });//Top right corner
		this->vertexData.at(1).SetPosition(glm::vec3{ screenPositionX - halfSpriteWidth, screenPositionY + singleSpriteHeight, 0.0f });//Top left corner
		this->vertexData.at(2).SetPosition(glm::vec3{ screenPositionX - halfSpriteWidth, screenPositionY, 0.0f });//Bottom left corner
		this->vertexData.at(3).SetPosition(glm::vec3{ screenPositionX - halfSpriteWidth, screenPositionY, 0.0f });//Bottom left corner
		this->vertexData.at(4).SetPosition(glm::vec3{ screenPositionX + halfSpriteWidth, screenPositionY, 0.0f });//Bottom right corner
		this->vertexData.at(5).SetPosition(glm::vec3{ screenPositionX + halfSpriteWidth, screenPositionY + singleSpriteHeight, 0.0f });//Top right corner

		glm::vec4 uvs;

		uint16 xTile = 0 % tileDimensions.x;
		uint16 yTile = 0 / tileDimensions.x;

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

	void SpriteTileSheet::SetTexture(const Blz::Graphics::Texture& texture)
	{
		this->texture = texture;
	}

	GLuint const SpriteTileSheet::GetTextureID() const
	{
		return texture.GetID();
	}

	Blz::Array<Vector3D, 6> const SpriteTileSheet::GetVertexData() const
	{
		return vertexData;
	}

	auto SpriteTileSheet::SetUVCoordinates(const glm::vec4 uvs) -> void
	{
		this->vertexData.at(0).SetUV(glm::vec2{ uvs.x + uvs.w, uvs.y + uvs.z });
		this->vertexData.at(1).SetUV(glm::vec2{ uvs.x, uvs.y + uvs.z });
		this->vertexData.at(2).SetUV(glm::vec2{ uvs.x, uvs.y });
		this->vertexData.at(3).SetUV(glm::vec2{ uvs.x, uvs.y });
		this->vertexData.at(4).SetUV(glm::vec2{ uvs.x + uvs.w, uvs.y });
		this->vertexData.at(5).SetUV(glm::vec2{ uvs.x + uvs.w, uvs.y + uvs.z });
	}
}