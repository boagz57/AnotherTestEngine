#pragma once
#include "GL/glew.h"

struct Position
{
	inline Position();
	inline Position(float x, float y, float z);
	float x;
	float y;
	float z;
};

Position::Position()
{}

Position::Position(float x, float y, float z) :
	x(x), y(y), z(z)
{}

struct Color
{
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

struct TextureCoordinate
{
	float u;
	float v;
};

struct Vector3D
{
	inline Vector3D();
	inline Vector3D(float x, float y, float z);

	Position position;
	Color color;
	TextureCoordinate textCoordinate;

	inline void setUV(float u, float v);
};

Vector3D::Vector3D()
{}

Vector3D::Vector3D(float x, float y, float z) :
	position(x, y, z)
{}

void Vector3D::setUV(float u, float v)
{
	this->textCoordinate.u = u;
	this->textCoordinate.v = v;
}