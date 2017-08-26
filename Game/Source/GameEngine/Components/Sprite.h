#pragma once
#include <GL\glew.h>
#include <GLM\vec4.hpp>
#include <GLM\vec2.hpp>
#include "Containers/SmallVector.h"
#include "../Vector3D.h"

class SpriteComponent
{
public:
	SpriteComponent();
	~SpriteComponent() = default;

	void SetScreenTargetLocation(sfloat screenPositionX, sfloat screenPositionY);
	void SetWidthAndHeight(sfloat width, sfloat height);
	void SetTextureID(GLuint id);
	GLuint GetTextureID();
	glm::vec4 SetUVs(uint16 index);

	Blz::SmallVector<Vector3D> GetVertexData();

private:
	float width = 0.0f;
	float height = 0.0f;
	GLuint textureID = 0;
	Blz::SmallVector<Vector3D> vertexData;
	glm::ivec2 tileDimensions;

	uint16 counter;
};

