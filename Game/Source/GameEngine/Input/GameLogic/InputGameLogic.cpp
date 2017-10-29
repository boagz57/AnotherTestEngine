#include "Fighter.h"
#include "InputGameLogic.h"

namespace Blz::Input
{
	auto GameLogic::Bind(const int32 key, Fighter* const fighter, std::function<void(Fighter*)> movementFunction) -> void
	{
		fighter->input.MakeFighterControllable();
		fighter->input.SetKeyBinding(key, movementFunction);
	}
}