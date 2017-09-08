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
			return fighters;
		}
	}
}