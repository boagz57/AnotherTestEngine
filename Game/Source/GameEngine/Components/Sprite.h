#pragma once
#include <GL\glew.h>
#include "../../Universal/SmallVector.h"
#include "../Vector3D.h"
#include "../Graphics/Texture.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	void Init(int16 screenCoordinateX, int16 screenCoordinateY, uint16 imageWidth, uint16 imageHeight, Blz::string imageFilePath);

	float x = 0.0f;
	float y = 0.0f;
	float width = 0.0f;
	float height = 0.0f;

	Blz::Graphics::Texture texture;
	Blz::SmallVector<Vector3D> vertexData;
};

