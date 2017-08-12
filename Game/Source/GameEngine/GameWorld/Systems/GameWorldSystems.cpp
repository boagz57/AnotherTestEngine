#include "GameWorldSystems.h"

namespace Blz
{
	namespace GameWorld
	{
		namespace System
		{
			TransformComponent Blz::GameWorld::System::SetFighterStartingPosition(TransformComponent fighterPosition, glm::vec2 fighterStartingPositions)
			{
				fighterPosition.SetPosition(fighterStartingPositions.x, fighterStartingPositions.y);

				return fighterPosition;
			}
		}
	}
}