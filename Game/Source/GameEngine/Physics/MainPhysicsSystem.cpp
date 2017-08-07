#include "../Scene.h"
#include "SubSystems\AABBCollisionSystem.h"
#include "SubSystems\MovementSystem.h"
#include "../../Universal/SmallVector.h"
#include "MainPhysicsSystem.h"

namespace Blz
{
	namespace Physics
	{
		MainSystem::MainSystem()
		{
		}

		MainSystem::~MainSystem()
		{
		}

		void MainSystem::Init()
		{
		}

		void MainSystem::Shutdown()
		{

		}

		Scene MainSystem::Update(Scene scene)
		{
			for (Fighter& fighter : scene.fighters)
			{
				Fighter newFighterState = MovementSystem(fighter);

				fighters.push_back(newFighterState);
			}

			Blz::SmallVector<Fighter> newFighterStates = AABBCollisionSystem(fighters);

			scene.fighters.swap(newFighterStates);
			fighters.clear();

			return scene;
		}
	}
}