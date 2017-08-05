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
	}
}