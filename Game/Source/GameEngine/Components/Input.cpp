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

	void Input::SetKeyBinding(int32 key, std::function<void(Fighter*)> movementFunction)
	{
		keyMovementBindings.emplace(key, movementFunction);
	}

	void Input::KeyPressed(int32 key, Fighter* fighter)
	{
		ERRASSERT(keyMovementBindings.find(key) != keyMovementBindings.end(), "Key not specified!");

		auto movementFunc = keyMovementBindings[key];
		movementFunc(fighter);
	}
}