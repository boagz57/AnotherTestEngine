#include "Fighter.h"
#include "Components/Input.h"
#include "InputManager.h"

namespace Blz
{
	namespace Input
	{
		void Manager::BindAxis(int32 key, Fighter* fighter, std::function<void(Fighter*)> movementFunction)
		{
			fighter->input.MakeFighterControllable();
			fighter->input.SetKeyBinding(key, movementFunction);
		}
	}
}

