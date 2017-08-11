#pragma once

class Component
{
public:
	Component(uint16 id);
	~Component();

	uint16 ID();

private:
	uint16 id = 0;
};
