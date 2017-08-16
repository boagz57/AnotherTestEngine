#pragma once
#include <GL\glew.h>
#include "Containers/SmallVector.h"
#include "../Vector3D.h"
#include "../Graphics/Texture.h"

class SpriteComponent
{
public:
	SpriteComponent();
	~SpriteComponent();

	void SetScreenTargetLocation(sfloat screenPositionX, sfloat screenPositionY);
	Blz::Graphics::Texture GetTexture();
	Blz::SmallVector<Vector3D> GetVertexData();

private:
	float width = 0.0f;
	float height = 0.0f;
	Blz::Graphics::Texture texture;
	Blz::SmallVector<Vector3D> vertexData;
};

