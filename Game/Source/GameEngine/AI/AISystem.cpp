#include "../Fighter.h"
#include "../Scene.h"
#include "AISystem.h"

namespace Blz
{
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

	void AISystem::Update(Scene& scene)
	{
		Fighter* player = nullptr;
		Fighter* AI = nullptr;

		for (Fighter& fighter : scene.fighters)
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

		if (player->GetPosition().x > 1)
			AI->AddToPosition(0.2f, 0.0f, 0.0f);
	}
}