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

		void SetScreenTargetLocationAndTileDimensions(sfloat screenPositionX, sfloat screenPositionY, glm::ivec2 spriteSheetTileDimensions);
		void SetWidthAndHeight(sfloat width, sfloat height);
		void SetTexture(Blz::Graphics::Texture texture);
		auto SetUVCoordinates(glm::vec4 uvs) -> void;


	private:
		float width = 200.0f;
		float height = 200.0f;
		GLuint textureID = 0;
		Blz::Array<Vector3D, 6> vertexData;
		glm::ivec2 tileDimensions;
	};
}
