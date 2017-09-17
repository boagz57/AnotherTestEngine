#include <functional>
#include "Input.h"

namespace Comp
{
	void Input::MakeFighterControllable()
	{
		isControllable = true;
	}

	bool Input::IsFighterControllable()
	{
		return isControllable;
	}

	void Input::SetKeyBinding(const int32 key, std::function<void(Fighter*)> movementFunction)
	{
		keyMovementBindings.emplace(key, movementFunction);
	}

	void Input::KeyPressed(const int32 key, Fighter * const fighter)
	{
		RUNTIME_ASSERT(keyMovementBindings.find(key) != keyMovementBindings.end(), "Input key has not been assigned!");

		auto movementFunc = keyMovementBindings[key];
		movementFunc(fighter);
	}
}