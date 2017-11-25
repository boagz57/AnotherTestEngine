#include <GL/glew.h>
#include <GLM\detail\type_vec2.hpp>
#include <GLM\detail\type_vec3.hpp>
#include "Graphics\Texture.h"
#include "SpriteSheet.h"

namespace Comp
{
	void SpriteSheet::Init(const Blz::Graphics::Texture& texture, const glm::ivec2 spriteSheetTileDimensions, uint16 scale /* = 1 */)
	{
		this->tileDimensions = spriteSheetTileDimensions;
		this->texture = texture;
		this->scaleFactor = scale;
	}

	void SpriteSheet::SetTexture(const Blz::Graphics::Texture& texture)
	{
		this->texture = texture;
	}

	GLuint const SpriteSheet::GetTextureID() const
	{
		BGZ_ERRASSERT(texture.GetID() != 0, "Spritesheet Texture has not been initialized properly!");
		return texture.GetID();
	}

	Blz::Array<Vector3D, 6> const SpriteSheet::GetVertexData() const
	{
		return vertexData;
	}

	void SpriteSheet::SetScreenPosition(const sfloat screenPositionX, const sfloat screenPositionY)
	{
		uint16 singleSpriteWidth = texture.GetWidth() / tileDimensions.x;
		uint16 singleSpriteHeight = texture.GetHeight() / tileDimensions.y;

		singleSpriteWidth *= this->scaleFactor;
		singleSpriteHeight *= this->scaleFactor;

		sfloat halfSpriteWidth = static_cast<sfloat>(singleSpriteWidth / 2);

		//Setting sprite origin at bottom middle of image 
		this->vertexData.at(0).SetPosition(glm::vec3{ screenPositionX + halfSpriteWidth, screenPositionY + singleSpriteHeight, 0.0f });//Top right corner
		this->vertexData.at(1).SetPosition(glm::vec3{ screenPositionX - halfSpriteWidth, screenPositionY + singleSpriteHeight, 0.0f });//Top left corner
		this->vertexData.at(2).SetPosition(glm::vec3{ screenPositionX - halfSpriteWidth, screenPositionY, 0.0f });//Bottom left corner
		this->vertexData.at(3).SetPosition(glm::vec3{ screenPositionX - halfSpriteWidth, screenPositionY, 0.0f });//Bottom left corner
		this->vertexData.at(4).SetPosition(glm::vec3{ screenPositionX + halfSpriteWidth, screenPositionY, 0.0f });//Bottom right corner
		this->vertexData.at(5).SetPosition(glm::vec3{ screenPositionX + halfSpriteWidth, screenPositionY + singleSpriteHeight, 0.0f });//Top right corner
	}

	auto SpriteSheet::SetUVCoordinates(const glm::vec4 uvs) -> void
	{
		this->vertexData.at(0).SetUV(glm::vec2{ uvs.x + uvs.w, uvs.y + uvs.z });
		this->vertexData.at(1).SetUV(glm::vec2{ uvs.x, uvs.y + uvs.z });
		this->vertexData.at(2).SetUV(glm::vec2{ uvs.x, uvs.y });
		this->vertexData.at(3).SetUV(glm::vec2{ uvs.x, uvs.y });
		this->vertexData.at(4).SetUV(glm::vec2{ uvs.x + uvs.w, uvs.y });
		this->vertexData.at(5).SetUV(glm::vec2{ uvs.x + uvs.w, uvs.y + uvs.z });
	}
}