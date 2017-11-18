#pragma once
#include <GLM\detail\type_vec3.hpp>
#include <GLM\detail\type_vec2.hpp>
#include <GL/glew.h>

class Vertex2D
{
public:
	inline Vertex2D();
	explicit inline Vertex2D(glm::vec2 position);
	inline Vertex2D(glm::vec2 position, glm::vec2 textureCoordinates);

	//Functions used for easier setting of attributes. Instead of having to write vec.position.x = blah, vec.position.y = blah, etc. 
	inline void SetPosition(glm::vec2 positionToSet);
	inline void SetUV(glm::vec2 textureCoordinatesToSet);

	glm::vec2 position;
	glm::vec2 textureCoordinates;
};

Vertex2D::Vertex2D()
{}

Vertex2D::Vertex2D(glm::vec2 position) :
	position(position)
{}

Vertex2D::Vertex2D(glm::vec2 position, glm::vec2 textureCoordinates) :
	position(position),
	textureCoordinates(textureCoordinates)
{}

void Vertex2D::SetPosition(glm::vec2 newPosition)
{
	this->position = newPosition;
}

void Vertex2D::SetUV(glm::vec2 newTextCoords)
{
	this->textureCoordinates = newTextCoords;
}