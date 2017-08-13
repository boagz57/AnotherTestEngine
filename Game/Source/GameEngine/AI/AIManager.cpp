#include "../Fighter.h"
#include "../Scene.h"
#include "../Fighter.h"
#include "Containers/SmallVector.h"
#include "AIManager.h"

namespace Blz
{
	namespace AI
	{
		Blz::SmallVector<Fighter> MoveAI(Blz::SmallVector<Fighter> fighters);

		AIManager::AIManager()
		{
		}

		AIManager::~AIManager()
		{
		}

		void AIManager::Init()
		{

		}

		void AIManager::Shutdown()
		{

		}

		void AIManager::Update(Scene& scene)
		{
			Blz::SmallVector<Fighter> updatedFighters = MoveAI(scene.fighters);
		}

		Blz::SmallVector<Fighter> MoveAI(Blz::SmallVector<Fighter> fighters)
		{
			Fighter* player = nullptr;
			Fighter* AI = nullptr;

			for (Fighter& fighter : fighters)
			{
				if (fighter.IsFighterControllable())
				{
					player = &fighter;
				}
				else
				{
					AI = &fighter;
				}
			}

			return fighters;
		}
	}
}