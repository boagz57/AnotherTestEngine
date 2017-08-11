#pragma once
#include "Component.h"
#include <GLM/vec3.hpp>

class VelocityComponent : public Component
{
public:
	VelocityComponent();

	glm::vec3 GetCurrentState();
	void Add(sfloat x, sfloat y);
	void ZeroOut();
	
private:
	glm::vec3 currentVelocity{ 0.0f, 0.0f, 0.0f };
};
