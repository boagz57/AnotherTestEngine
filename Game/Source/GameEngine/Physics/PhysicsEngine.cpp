#include "../Scene.h"
#include "Systems/PhysicsSystems.h"
#include "Components/Position.h"
#include "PhysicsEngine.h"

namespace Blz
{
	namespace Physics
	{
		void Engine::Init()
		{
		}

		void Engine::Shutdown()
		{

		}

		void Engine::Update(Scene& scene)
		{
			for (Fighter& fighter : scene.fighters)
			{
				Comp::Position newFighterPosition = CompSystem::MoveFighter(fighter.GetComponent<Comp::Transform>(), fighter.GetComponent<Comp::Position>());

				fighter.Insert<Comp::Position>(newFighterPosition);
			}
		}
	}
}