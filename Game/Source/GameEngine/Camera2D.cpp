#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include "Camera2D.h"

namespace Blz
{
	Camera2D::Camera2D() :
		position(0.0f, 0.0f),
		cameraNeedsUpdated(true),
		scale(0.0f),
		orthoMatrix(1.0f),
		transformationMatrix(1.0f),
		screenWidth(500),
		screenHeight(500)
	{
	}

	Camera2D::~Camera2D()
	{
	}

	void Camera2D::Init(int32 screenWidth, int32 screenHeight)
	{
		this->screenWidth = screenWidth;
		this->screenHeight = screenHeight;
		orthoMatrix = glm::ortho(0.0f, (sfloat)screenWidth, 0.0f, (sfloat)screenHeight);
	}

	void Camera2D::Update()
	{
		if (cameraNeedsUpdated)
		{
			transformationMatrix = glm::translate(orthoMatrix, glm::vec3(-position.x, -position.y, 0.0f));
			transformationMatrix = glm::scale(transformationMatrix, glm::vec3(scale, scale, 0.0f));
			cameraNeedsUpdated = false;
		}
	}
}