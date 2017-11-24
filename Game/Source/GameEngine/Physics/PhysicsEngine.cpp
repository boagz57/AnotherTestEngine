#include "../Scene.h"
#include "Fighter.h"
#include "Components/Position.h"
#include "Components\Velocity.h"
#include "Components\Movement.h"
#include "Components\RectangleCollision.h"
#include "PhysicsEngine.h"

namespace Blz::Physics
{
	struct Components
	{
		Comp::Velocity velocity;
		Comp::Position position;
		Comp::Movement movement;
	};

	static auto CollisionSystem (Comp::RectangleCollision fighter1CollBox, Comp::Position fighter1Position, Comp::RectangleCollision fighter2CollBox, Comp::Position fighter2Position) -> bool;

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

		bool fightersCollided = CollisionSystem(fighter1->collisionBox, fighter1->position, fighter2->collisionBox, fighter2->position);

		if (fightersCollided)
			LOG("Collision!");
	};

	auto CollisionSystem(Comp::RectangleCollision fighter1CollBox, Comp::Position fighter1Position, Comp::RectangleCollision fighter2CollBox, Comp::Position fighter2Position) -> bool
	{
		fighter1CollBox.position = fighter1Position.GetCurrentPosition();
		fighter2CollBox.position = fighter2Position.GetCurrentPosition();

		static glm::vec2 f1BottomLeftCoords{};
		static glm::vec2 f1TopRightCoords{};
		static glm::vec2 f2BottomLeftCoords{};
		static glm::vec2 f2TopRightCoords{};

		{//Update fighter collision box coordinates
			f1BottomLeftCoords = { fighter1CollBox.position.x - (fighter1CollBox.width / 2),
				fighter1CollBox.position.y };
			f1TopRightCoords = { fighter1CollBox.position.x + (fighter1CollBox.width / 2),
				fighter1CollBox.position.y + fighter1CollBox.height };

			f2BottomLeftCoords = { fighter2CollBox.position.x - (fighter2CollBox.width / 2),
				fighter2CollBox.position.y };
			f2TopRightCoords = { fighter2CollBox.position.x + (fighter2CollBox.width / 2),
				fighter2CollBox.position.y + fighter2CollBox.height };
		}

		//Exit returning NO intersection between bounding boxes
		if (f1TopRightCoords.x < f2BottomLeftCoords.x ||
			f1BottomLeftCoords.x > f2TopRightCoords.x)
		{
			return false;
		}

		//Exit returning NO intersection between bounding boxes
		if (f1TopRightCoords.y < f2BottomLeftCoords.y ||
			f1BottomLeftCoords.y > f2TopRightCoords.y)
		{
			return false;
		}

		//Else intersection and thus collision has occured!
		return true;
	};
}