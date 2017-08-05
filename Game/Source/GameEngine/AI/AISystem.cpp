#include "../Fighter.h"
#include "../Scene.h"
#include "../Fighter.h"
#include "../../Universal/SmallVector.h"
#include "AISystem.h"

namespace Blz
{
	Blz::SmallVector<Fighter> MoveAI(Blz::SmallVector<Fighter> fighters);

	AISystem::AISystem()
	{
	}

	AISystem::~AISystem()
	{
	}

	void AISystem::Init()
	{

	}

	void AISystem::Shutdown()
	{

	}

	Scene AISystem::Update(Scene scene)
	{
		Blz::SmallVector<Fighter> updatedFighters = MoveAI(scene.fighters);

		scene.fighters = updatedFighters;
		return scene;
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

		if (player->position.GetCurrentState().x > 0)
			AI->position.Add(20.0f, 0.0f);

		return fighters;
	}
}