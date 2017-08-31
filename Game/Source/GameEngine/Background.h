#pragma once
#include "Components/Sprite.h"
#include "Components/ComponentHolder.h"

class Background :
	ComponentHolder<SpriteComponent>
{
public:
	Background() = default;
	~Background() = default;

	template<class T>
	T GetComponent();

	template<class T>
	void Insert(T comp);
};

template<class T>
inline T Background::GetComponent()
{
	return this->ComponentHolder<T>::component;
}

template<class T>
inline void Background::Insert(T comp)
{
	this->ComponentHolder<T>::component = comp;
}
