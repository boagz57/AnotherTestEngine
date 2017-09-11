#include "Fighter.h"
#include "Components/Input.h"
#include "InputManager.h"

namespace Blz
{
	namespace Input
	{
		void Manager::SetFighterToBeControllable(Fighter* fighter)
		{
			fighter->input.MakeFighterControllable();
		}
	}
}

