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
}