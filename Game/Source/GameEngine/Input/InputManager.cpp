#include "Fighter.h"
#include "Components/Input.h"
#include "InputManager.h"

namespace Blz
{
	namespace Input
	{
		void Manager::SetFighterToBeControllable(Fighter* fighter)
		{
			Comp::Input input = fighter->GetComponent<Comp::Input>();
			input.MakeFighterControllable();

			fighter->Insert(input);
		}
	}
}

