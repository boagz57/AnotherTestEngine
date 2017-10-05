#pragma once
#include <GL\glew.h>
#include <GLM\vec4.hpp>
#include <GLM\vec2.hpp>
#include "Containers/Array.h"
#include "Graphics\Texture.h"
#include "../Vector3D.h"

namespace Comp
{
	class SpriteSheet
	{
	public:
		SpriteSheet() = default;
		~SpriteSheet() = default;

		void Init(const Blz::Graphics::Texture& texture, const glm::ivec2 spriteSheetTileDimensions, uint16 scaleTextureBy = 1);

		GLuint const GetTextureID() const;

		auto GetDimensions() const->glm::ivec2 { return tileDimensions; };

		Blz::Array<Vector3D, 6> const GetVertexData() const;

		void SetSpriteScreenPosition(const sfloat screenPositionX, const sfloat screenPosotionY);

		void SetTexture(const Blz::Graphics::Texture& texture);

		auto SetUVCoordinates(const glm::vec4 uvs) -> void;

	private:
		Blz::Graphics::Texture texture{};
		Blz::Array<Vector3D, 6> vertexData;
		glm::ivec2 tileDimensions;
		uint16 scaleFactor{0};
	};
}
