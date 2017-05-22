#include "Input.h"

namespace Blz
{
	//Initialize Static memory
	UMap<uint, bool> Input::keyMap;

	Input::Input()
	{
	}

	Input::~Input()
	{
	}

	void Input::pressKey(uint keyID)
	{
		keyMap[keyID] = true;
	}

	void Input::releaseKey(uint keyID)
	{
		keyMap[keyID] = false;
	}

	bool Input::IsKeyPressed(uint keyID)
	{
		return keyMap[keyID];
	}

}