#pragma once
#include <GLM\detail\type_vec3.hpp>
#include <GLM\detail\type_vec2.hpp>
#include <GL/glew.h>

class Vector3D
{
public:
	inline Vector3D();
	explicit inline Vector3D(glm::vec3 position);
	inline Vector3D(glm::vec3 position, glm::vec2 textureCoordinates);

	//Functions used for easier setting of attributes. Instead of having to write vec.position.x = blah, vec.position.y = blah, etc. 
	inline void SetPosition(glm::vec3 positionToSet);
	inline void SetUV(glm::vec2 textureCoordinatesToSet);

	glm::vec3 position{};
	glm::vec2 textureCoordinates{};
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

void Vector3D::SetPosition(glm::vec3 newPosition)
{
	this->position = newPosition;
}

void Vector3D::SetUV(glm::vec2 newTextCoords)
{
	this->textureCoordinates = newTextCoords;
}