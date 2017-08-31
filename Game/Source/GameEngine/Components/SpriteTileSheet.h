#pragma once
#include <GL\glew.h>
#include <GLM\vec4.hpp>
#include <GLM\vec2.hpp>
#include "Containers/SmallVector.h"
#include "../Vector3D.h"

class SpriteTileSheetComponent
{
public:
	SpriteTileSheetComponent();
	~SpriteTileSheetComponent() = default;

	void SetScreenTargetLocationAndTileDimensions(sfloat screenPositionX, sfloat screenPositionY, glm::ivec2 spriteSheetTileDimensions);
	void SetWidthAndHeight(sfloat width, sfloat height);
	void SetTextureID(GLuint id);
	GLuint const GetTextureID() const;
	void SetUVs(const uint16 startingIndex);
	uint16 const CheckIndex() const;

	Blz::SmallVector<Vector3D> const GetVertexData() const;

private:
	float width = 0.0f;
	float height = 0.0f;
	GLuint textureID = 0;
	Blz::SmallVector<Vector3D> vertexData;
	glm::ivec2 tileDimensions;
	uint16 index = 0;
};

