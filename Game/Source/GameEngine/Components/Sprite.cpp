#include "Graphics\Texture.h"
#include "Sprite.h"

namespace Comp
{
	void Sprite::SetScreenTargetLocation(const sfloat screenPositionX, const sfloat screenPositionY)
	{
		sfloat halfWidth = this->width / 2;

		//Setting sprite origin at bottom middle of image by subtracting half width 
		this->vertexData.at(0).SetPosition(glm::vec3{ screenPositionX + (this->width - halfWidth), screenPositionY + this->height, 0.0f });//Top right corner
		this->vertexData.at(1).SetPosition(glm::vec3{ screenPositionX - halfWidth, screenPositionY + height, 0.0f });//Top left corner
		this->vertexData.at(2).SetPosition(glm::vec3{ screenPositionX - halfWidth, screenPositionY, 0.0f });//Bottom left corner
		this->vertexData.at(3).SetPosition(glm::vec3{ screenPositionX - halfWidth, screenPositionY, 0.0f });//Bottom left corner
		this->vertexData.at(4).SetPosition(glm::vec3{ screenPositionX + (this->width - halfWidth), screenPositionY, 0.0f });//Bottom right corner
		this->vertexData.at(5).SetPosition(glm::vec3{ screenPositionX + (this->width - halfWidth), screenPositionY + this->height, 0.0f });//Top right corner

		this->vertexData.at(0).SetUV(glm::vec2{ 1.0f, 1.0f });
		this->vertexData.at(1).SetUV(glm::vec2{ 0.0f, 1.0f });
		this->vertexData.at(2).SetUV(glm::vec2{ 0.0f, 0.0f });
		this->vertexData.at(3).SetUV(glm::vec2{ 0.0f, 0.0f });
		this->vertexData.at(4).SetUV(glm::vec2{ 1.0f, 0.0f });
		this->vertexData.at(5).SetUV(glm::vec2{ 1.0f, 1.0f });
	}

	void Sprite::SetWidthAndHeight(const sfloat width, const sfloat height)
	{
		this->width = width;
		this->height = height;
	}

	void Sprite::SetTexture(const Blz::Graphics::Texture& texture)
	{
		this->textureID = texture.ID();
	}

	GLuint const Sprite::GetTextureID() const
	{
		return textureID;
	}

	Blz::Array<Vector3D, 6> const Sprite::GetVertexData() const
	{
		return vertexData;
	}
}