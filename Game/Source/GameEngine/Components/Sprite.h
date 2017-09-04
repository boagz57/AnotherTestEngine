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

		void SetScreenTargetLocation(sfloat screenPositionX, sfloat screenPositionY);
		void SetWidthAndHeight(sfloat width, sfloat height);
		void SetTexture(Blz::Graphics::Texture texture);
		GLuint const GetTextureID() const;

		Blz::Array<Vector3D, 6> const GetVertexData() const;

	private:
		float width = 200.0f;
		float height = 200.0f;
		GLuint textureID = 0;
		Blz::Array<Vector3D, 6> vertexData;
	};
}