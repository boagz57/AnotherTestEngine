#include "Fighter.h"
#include "Components/Input.h"
#include "InputManager.h"

namespace Blz
{
	namespace Input
	{
		auto Manager::Bind(const int32 key, Fighter* const fighter, std::function<void(Fighter*)> movementFunction) -> void
		{
			fighter->input.MakeFighterControllable();
			fighter->input.SetKeyBinding(key, movementFunction);
		}
	}
}

