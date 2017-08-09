#include "../../../Universal/SmallVector.h"
#include "../../Fighter.h"
#include "AABBCollisionSystem.h"

namespace Blz
{
	namespace Physics
	{
		//Helper functions
		void CheckForCollision(Fighter fighter1, Fighter fighter2);

		Blz::SmallVector<Fighter> AABBCollisionSystem(Blz::SmallVector<Fighter> fighters)
		{
			Fighter fighter1;
			Fighter fighter2;

			for (Fighter fighter : fighters)
			{
				fighter.collisionBox.SetMaxCoordinateOffset(100.0f, 200.0f);
				fighter.collisionBox.SetMinCoordinateOffset(-100.0f, 0.0f);

				fighter.collisionBox.SetMaxCoordinatePosition(fighter.transform.GetCurrentPosition().x, fighter.transform.GetCurrentPosition().y);
				fighter.collisionBox.SetMinCoordinatePosition(fighter.transform.GetCurrentPosition().x, fighter.transform.GetCurrentPosition().y);

				if (fighter.IsFighterControllable())
					fighter1 = fighter;
				else
					fighter2 = fighter;
			}

			CheckForCollision(fighter1, fighter2);

			return fighters;
		}

		//Helper function definitions
		void CheckForCollision(Fighter fighter1, Fighter fighter2)
		{
			glm::vec2 fighter1Max = fighter1.collisionBox.GetCurrentMaxCoordinatePosition();
			glm::vec2 fighter2Max = fighter2.collisionBox.GetCurrentMaxCoordinatePosition();

			glm::vec2 fighter1Min = fighter1.collisionBox.GetCurrentMinCoordinatePosition();
			glm::vec2 fighter2Min = fighter2.collisionBox.GetCurrentMinCoordinatePosition();

			//Exit returning NO intersection between bounding boxes
			if (fighter1Max.x < fighter2Min.x || fighter1Min.x > fighter2Max.x)
				return;
			//Exit returning NO intersection between bounding boxes
			if (fighter1Max.y < fighter2Min.y || fighter1Min.y > fighter2Max.y)
				return;

			//If haven't exited yet then a collision occurred
			LOG("Collision occurred!");
		}
	}
}
