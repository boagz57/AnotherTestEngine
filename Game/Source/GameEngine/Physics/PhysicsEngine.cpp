#include "../Scene.h"
#include "Fighter.h"
#include "Components/Position.h"
#include "Components\Velocity.h"
#include "Components\Movement.h"
#include "PhysicsEngine.h"

namespace Blz::Physics
{
	struct Components
	{
		Comp::Velocity velocity;
		Comp::Position position;
		Comp::Movement movement;
	};

	auto Engine::Init(Scene& scene) -> void
	{
		//caputre references to each individual fighter to check collisions in physics update
		for (uint16 i = 0; i < scene.fighters.size(); ++i)
		{
			if (i == 0)
				fighter1 = scene.fighters.at(i);
			else
				fighter2 = scene.fighters.at(i);
		}
	}

	auto Engine::Shutdown() -> void
	{

	}

	auto Engine::Update(Scene& scene, sfloat deltaTime) -> void
	{
		ec.AddContext("When updating Physics engine");

		for (Fighter* fighter : scene.fighters)
		{
			auto AcceptedComponents = [&fighter, deltaTime](
				Comp::Velocity fighterVelocity, 
				Comp::Position fighterPosition, 
				Comp::Movement fighterMovement) -> Components
			{
				fighterPosition.Add(fighterVelocity.GetCurrentState().x * deltaTime, fighterVelocity.GetCurrentState().y * deltaTime);

				fighterVelocity.Add(0.0f, (fighterMovement.GetGravity() * deltaTime));

				{//Set window borders
					fighterPosition.ClampMaxPositionTo(c_levelBorderMaxX, c_levelBorderMaxY);
					fighterPosition.ClampMinPositionTo(c_levelBorderMinX, c_groundLevel);
				}

				//Prevent velocity from going more and more negative when on the ground
				if (fighterPosition.GetCurrentPosition().y == c_groundLevel)
					fighterVelocity.ZeroOutY();

				return { fighterVelocity, fighterPosition, fighterMovement };
			};

			auto [updatedFighterVelocity, updatedFighterPosition, updatedFighterMovement] = 
				AcceptedComponents(fighter->velocity, fighter->position, fighter->movement);

			fighter->velocity = updatedFighterVelocity;
			fighter->position = updatedFighterPosition;
			fighter->movement = updatedFighterMovement;
		};

		[&]()//AABB Collsion System
		{
			fighter1->collisionBox.position = scene.fighters.at(0)->position.GetCurrentPosition();
			fighter2->collisionBox.position = scene.fighters.at(1)->position.GetCurrentPosition();

			static glm::vec2 f1BottomLeftCoords{};
			static glm::vec2 f1TopRightCoords{};
			static glm::vec2 f2BottomLeftCoords{};
			static glm::vec2 f2TopRightCoords{};

			{//Update fighter collision box coordinates
				f1BottomLeftCoords = { fighter1->collisionBox.position.x - (fighter1->collisionBox.width / 2), 
					fighter1->collisionBox.position.y };
				f1TopRightCoords = { fighter1->collisionBox.position.x + (fighter1->collisionBox.width / 2), 
					fighter1->collisionBox.position.y + fighter1->collisionBox.height };

				f2BottomLeftCoords = { fighter2->collisionBox.position.x - (fighter2->collisionBox.width / 2),
					fighter2->collisionBox.position.y };
				f2TopRightCoords = { fighter2->collisionBox.position.x + (fighter2->collisionBox.width / 2), 
					fighter2->collisionBox.position.y + fighter2->collisionBox.height };
			}

			//Exit returning NO intersection between bounding boxes
			if (f1TopRightCoords.x < f2BottomLeftCoords.x ||
				f1BottomLeftCoords.x > f2TopRightCoords.x)
			{
				return;
			}

			//Exit returning NO intersection between bounding boxes
			if (f1TopRightCoords.y < f2BottomLeftCoords.y ||
				f1BottomLeftCoords.y > f2TopRightCoords.y)
			{
				return;
			}

			//Else intersection and thus collision has occured!
			LOG("Collision!\n");
		}();
	};
}