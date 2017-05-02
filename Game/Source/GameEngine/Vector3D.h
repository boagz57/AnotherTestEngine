#pragma once
#include "GL/glew.h"

struct Position
{
	Position();
	Position(float x, float y, float z);
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

struct Vector3D
{
	Vector3D();
	Vector3D(float x, float y, float z);

	Position position;
	Color color;
};

Vector3D::Vector3D()
{}

Vector3D::Vector3D(float x, float y, float z) :
	position(x, y, z)
{}