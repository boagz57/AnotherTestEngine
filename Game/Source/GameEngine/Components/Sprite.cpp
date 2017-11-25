#include "Graphics\Texture.h"
#include "Sprite.h"

namespace Comp
{
	auto Sprite::Init(Blz::Graphics::Texture& texture, uint16 scale /* = 1*/) -> void
	{
		this->texture = texture;
		scaleFactor = scale;
	}

	void Sprite::SetScreenPosition(const sfloat screenPositionX, const sfloat screenPositionY)
	{
		uint16 textureWidth = this->texture.GetWidth();
		uint16 textureHeight = this->texture.GetHeight();

		textureWidth *= scaleFactor;
		textureHeight *= scaleFactor;

		sfloat halfTextureWidth = static_cast<sfloat>(textureWidth / 2);

		//Setting sprite origin at bottom middle of image by subtracting half width 
		this->vertexData.at(0).SetPosition(glm::vec3{ screenPositionX + halfTextureWidth, screenPositionY + textureHeight, 0.0f });//Top right corner
		this->vertexData.at(1).SetPosition(glm::vec3{ screenPositionX - halfTextureWidth, screenPositionY + textureHeight, 0.0f });//Top left corner
		this->vertexData.at(2).SetPosition(glm::vec3{ screenPositionX - halfTextureWidth, screenPositionY, 0.0f });//Bottom left corner
		this->vertexData.at(3).SetPosition(glm::vec3{ screenPositionX - halfTextureWidth, screenPositionY, 0.0f });//Bottom left corner
		this->vertexData.at(4).SetPosition(glm::vec3{ screenPositionX + halfTextureWidth, screenPositionY, 0.0f });//Bottom right corner
		this->vertexData.at(5).SetPosition(glm::vec3{ screenPositionX + halfTextureWidth, screenPositionY + textureHeight, 0.0f });//Top right corner

		this->vertexData.at(0).SetUV(glm::vec2{ 1.0f, 1.0f });
		this->vertexData.at(1).SetUV(glm::vec2{ 0.0f, 1.0f });
		this->vertexData.at(2).SetUV(glm::vec2{ 0.0f, 0.0f });
		this->vertexData.at(3).SetUV(glm::vec2{ 0.0f, 0.0f });
		this->vertexData.at(4).SetUV(glm::vec2{ 1.0f, 0.0f });
		this->vertexData.at(5).SetUV(glm::vec2{ 1.0f, 1.0f });
	}

	void Sprite::SetTexture(const Blz::Graphics::Texture& texture)
	{
		this->texture = texture;
	}

	GLuint const Sprite::GetTextureID() const
	{
		BGZ_ERRASSERT(texture.GetID() != 0, "Spritesheet Texture has not been initialized properly!");
		return texture.GetID();
	}

	Blz::Array<Vector3D, 6> const Sprite::GetVertexData() const
	{
		return vertexData;
	}
}