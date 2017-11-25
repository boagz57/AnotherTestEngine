#include <functional>
#include "Input.h"

namespace Comp
{
	void Input::MakeFighterControllable()
	{
		Controllable = true;
	}

	bool Input::IsControllable()
	{
		return Controllable;
	}

	const bool Input::IsKeyPressed()
	{
		bool keyPressed = false;

		for(auto& key : keyMap)
		{ 
			keyPressed = key.second;

			if (keyPressed)
				return true;
		}

		return false;
	}

	void Input::SetKeyBinding(const int32 key, std::function<void(Fighter*)> movementFunction)
	{
		keyMovementBindings.emplace(key, movementFunction);
	}

	void Input::KeyPressed(const int32 key, Fighter * const fighter)
	{
		BGZ_RUNTIME_ASSERT(keyMovementBindings.find(key) != keyMovementBindings.end(), "Input key has not been assigned!");

		auto action = keyMovementBindings[key];
		action(fighter);
	}
}