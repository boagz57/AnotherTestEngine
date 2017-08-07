#include "../../Fighter.h"
#include "MovementSystem.h"

namespace Blz
{
	namespace Physics
	{
		Fighter MovementSystem(Fighter fighter)
		{
			//Set how much fighter will be translated within world
			fighter.transform.TranslatePosition(fighter.velocity.GetCurrentState().x, fighter.velocity.GetCurrentState().y);

			//Set fighters new world position
			fighter.position.Add(fighter.velocity.GetCurrentState().x, fighter.velocity.GetCurrentState().y);

			//To stop fighter movement from continuing to move in the direction of input
			fighter.velocity.ZeroOut();

			return fighter;
		}
	}
}