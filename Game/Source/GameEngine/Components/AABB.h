#pragma once
#include <GLM/vec2.hpp>

class AABBComponent
{
public:
	inline glm::vec2 GetCurrentMinCoordinateOffset();
	inline glm::vec2 GetCurrentMaxCoordinateOffset();

	inline glm::vec2 GetCurrentMinCoordinatePosition();
	inline glm::vec2 GetCurrentMaxCoordinatePosition();

	inline void SetMinCoordinateOffset(sfloat x, sfloat y);
	inline void SetMaxCoordinateOffset(sfloat x, sfloat y);

	inline void SetMinCoordinatePosition(sfloat fighterPositionX, sfloat fighterPositionY);
	inline void SetMaxCoordinatePosition(sfloat figtherPositionX, sfloat fighterPositionY);

private:
	glm::vec2 bottomLeftCoordinateOffset;
	glm::vec2 topRightCoordinateOffset;

	glm::vec2 bottomLeftCoordinatePosition;
	glm::vec2 topRightCoordinatePosition;
};

glm::vec2 AABBComponent::GetCurrentMinCoordinateOffset()
{
	return bottomLeftCoordinateOffset;
}

glm::vec2 AABBComponent::GetCurrentMaxCoordinateOffset()
{
	return topRightCoordinateOffset;
}

glm::vec2 AABBComponent::GetCurrentMinCoordinatePosition()
{
	return topRightCoordinatePosition;
}

glm::vec2 AABBComponent::GetCurrentMaxCoordinatePosition()
{
	return bottomLeftCoordinatePosition;
}

void AABBComponent::SetMinCoordinateOffset(sfloat x, sfloat y)
{
	this->bottomLeftCoordinateOffset.x = x;
	this->bottomLeftCoordinateOffset.y = y;
}

void AABBComponent::SetMaxCoordinateOffset(sfloat x, sfloat y)
{
	this->topRightCoordinateOffset.x = x;
	this->topRightCoordinateOffset.y = y;
}

void AABBComponent::SetMinCoordinatePosition(sfloat fighterX, sfloat fighterY)
{
	this->bottomLeftCoordinatePosition.x += fighterX;
	this->bottomLeftCoordinatePosition.y += fighterY;
}

void AABBComponent::SetMaxCoordinatePosition(sfloat fighterX, sfloat fighterY)
{
	this->topRightCoordinatePosition.x += fighterX;
	this->topRightCoordinatePosition.y += fighterY;
}