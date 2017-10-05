#pragma once
#include <GL\glew.h>
#include <GLM\vec4.hpp>
#include <GLM\vec2.hpp>
#include "Containers/Array.h"
#include "Graphics\Texture.h"
#include "../Vector3D.h"

namespace Comp
{
	class SpriteTileSheet
	{
	public:
		SpriteTileSheet() = default;
		~SpriteTileSheet() = default;

		GLuint const GetTextureID() const;
		auto GetTileDimensions() const->glm::ivec2 { return tileDimensions; };
		Blz::Array<Vector3D, 6> const GetVertexData() const;

		void Init(const sfloat startingScreenPositionX, const sfloat startingScreenPositionY, const glm::ivec2 spriteSheetTileDimensions,
			      uint16 scale = 1);

		void SetTexture(const Blz::Graphics::Texture& texture);
		auto SetUVCoordinates(const glm::vec4 uvs) -> void;

	private:
		Blz::Graphics::Texture texture{};
		Blz::Array<Vector3D, 6> vertexData;
		glm::ivec2 tileDimensions;
	};
}
