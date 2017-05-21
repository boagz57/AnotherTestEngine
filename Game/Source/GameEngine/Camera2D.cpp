#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <iostream>
#include "Camera2D.h"

namespace Blz
{
	Camera2D::Camera2D() :
		position(0.0f, 0.0f),
		cameraNeedsUpdated(true),
		scale(1.0f),
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
		orthoMatrix = glm::ortho(0.0f, static_cast<sfloat>(screenWidth), 0.0f, static_cast<sfloat>(screenHeight));
	}

	void Camera2D::Update()
	{
		if (cameraNeedsUpdated)
		{
            //Camera Translation                                //Add half of screenwidth/height to center the point of translation
			transformationMatrix = glm::translate(orthoMatrix, glm::vec3(-position.x + (screenWidth/2), position.y + (screenHeight / 2), 0.0f));

		    //Camera Scaling                 //Identity matrix  //Scaling this way centers the scale to middle of screen
			transformationMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale, scale, 0.0f)) * transformationMatrix;
			cameraNeedsUpdated = false;
		}
	}
}