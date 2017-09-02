#pragma once
#include "Vector3D.h"

namespace Comp
{
	class Sprite
	{
	public:
		Sprite();
		~Sprite() = default;

		void SetScreenTargetLocation(sfloat screenPositionX, sfloat screenPositionY);
		void SetWidthAndHeight(sfloat width, sfloat height);
		void SetTextureID(GLuint id);
		GLuint const GetTextureID() const;

		Blz::SmallVector<Vector3D> const GetVertexData() const;

	private:
		float width = 0.0f;
		float height = 0.0f;
		GLuint textureID = 0;
		Blz::SmallVector<Vector3D> vertexData;
	};
}