#pragma once

template<class T>
class ComponentHolder
{
public:
	ComponentHolder() = default;
	~ComponentHolder() = default;

protected:
	T component;
};
