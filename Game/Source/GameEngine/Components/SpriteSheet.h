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

		auto Init(const Blz::Graphics::Texture& texture, const glm::ivec2 spriteSheetTileDimensions, uint16 scaleTextureBy = 1) -> void;

		auto GetTextureID() const -> const GLuint;

		auto GetDimensions() const->glm::ivec2 { return tileDimensions; };

		auto GetVertexData() const -> const Blz::Array<Vector3D, 6>;

		auto SetScreenPosition(const sfloat screenPositionX, const sfloat screenPosotionY) -> void;

		auto SetTexture(const Blz::Graphics::Texture& texture) -> void;

		auto SetUVCoordinates(const glm::vec4 uvs) -> void;

	private:
		Blz::Graphics::Texture texture{};
		Blz::Array<Vector3D, 6> vertexData;
		glm::ivec2 tileDimensions;
		uint16 scaleFactor{1};
	};
}
