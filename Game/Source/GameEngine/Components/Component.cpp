#include "Component.h"

Component::Component(uint16 id) :
	id(id)
{
}

Component::~Component()
{
}

uint16 Component::ID()
{
	return this->id;
}
