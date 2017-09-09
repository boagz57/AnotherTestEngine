#include "../Fighter.h"
#include "../Scene.h"
#include "../Fighter.h"
#include "Containers/SmallVector.h"
#include "AIEngine.h"

namespace Blz
{
	namespace AI
	{
		Blz::SmallVector<Fighter> MoveAI(Blz::SmallVector<Fighter> fighters);

		void Engine::Init()
		{

		}

		void Engine::Shutdown()
		{

		}

		void Engine::Update(Scene& scene)
		{
			Blz::SmallVector<Fighter> updatedFighters = MoveAI(scene.fighters);
		}

		Blz::SmallVector<Fighter> MoveAI(Blz::SmallVector<Fighter> fighters)
		{
			return fighters;
		}
	}
}