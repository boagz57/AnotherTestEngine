#pragma once
#include "Graphics\Texture.h"
#include "Containers\Array.h"
#include "Vector3D.h"

namespace Comp
{
	class Sprite
	{
	public:
		Sprite() = default;
		~Sprite() = default;

		auto Init(Blz::Graphics::Texture& texture, uint16 scaleImageBy = 1) -> void;

		auto SetScreenPosition(const sfloat screenPositionX, const sfloat screenPositionY) -> void;

		auto SetTexture(const Blz::Graphics::Texture& texture) -> void;

		auto GetTextureID() const -> const GLuint;

		auto GetVertexData() const -> const Blz::Array<Vector3D, 6>;

	private:
		uint16 scaleFactor{ 1 };
		Blz::Graphics::Texture texture{};
		Blz::Array<Vector3D, 6> vertexData{};
	};
}