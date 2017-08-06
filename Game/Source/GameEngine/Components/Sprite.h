#pragma once
#include <GL\glew.h>
#include "../../Universal/SmallVector.h"
#include "../Vector3D.h"
#include "../Graphics/Texture.h"

class Sprite
{
public:
	Sprite();
	Sprite(Blz::string const imageFilePath, uint16 const imageWidth, uint16 const imageHeight);
	~Sprite();

	void SetTargetPosition(sfloat screenPositionX, sfloat screenPositionY);
	Blz::Graphics::Texture GetTexture();
	Blz::SmallVector<Vector3D> GetVertexData();

	float width = 0.0f;
	float height = 0.0f;

private:
	Blz::Graphics::Texture texture;
	Blz::SmallVector<Vector3D> vertexData;
};

