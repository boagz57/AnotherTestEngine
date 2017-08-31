#pragma once
#include <GLM/vec2.hpp>

class VelocityComponent 
{
public:
	VelocityComponent() = default;

	glm::vec2 const GetCurrentState() const;
	void Add(sfloat x, sfloat y);
	void ZeroOut();
	
private:
	glm::vec2 currentVelocity{ 0.0f, 0.0f };
};
