#pragma once
#include <GLM\detail\type_vec3.hpp>
#include <GLM\detail\type_vec2.hpp>
#include <GL/glew.h>

class Vector3D
{
public:
	inline Vector3D();
	inline Vector3D(glm::vec3 position);
	inline Vector3D(glm::vec3 position, glm::vec2 textureCoordinates);

	inline glm::vec3 GetPosition();
	inline glm::vec2 GetTextCoords();
	inline void SetPosition(glm::vec3 positionToSet);
	inline void SetUV(glm::vec2 textureCoordinatesToSet);

private:
	glm::vec3 position;
	glm::vec2 textureCoordinates;
};

Vector3D::Vector3D()
{}

Vector3D::Vector3D(glm::vec3 position) :
	position(position)
{}

Vector3D::Vector3D(glm::vec3 position, glm::vec2 textureCoordinates) :
	position(position),
	textureCoordinates(textureCoordinates)
{}

glm::vec3 Vector3D::GetPosition()
{
	return position;
}

glm::vec2 Vector3D::GetTextCoords()
{
	return textureCoordinates;
}

void Vector3D::SetPosition(glm::vec3 newPosition)
{
	this->position = newPosition;
}

void Vector3D::SetUV(glm::vec2 newTextCoords)
{
	this->textureCoordinates = newTextCoords;
}