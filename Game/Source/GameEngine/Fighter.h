#pragma once
#include <memory>
#include <GLM/vec3.hpp>
#include "Graphics/Texture.h"
#include "Containers/Map.h"
#include "Components/Animation.h"
#include "Components\Movement.h"
#include "Components/SpriteTileSheet.h"
#include "Components/Velocity.h"
#include "Components/Input.h"
#include "Components/Transform.h"
#include "Components\Position.h"

namespace Blz { namespace Physics { class Manager; }; };
namespace Blz { namespace Input { class Manager; }; };
namespace Blz { namespace Animation { class Manager; }; };

class Fighter 
{
public:
	Fighter() = default;
	Fighter(sfloat startingWorldPositionX, sfloat startingWorldPositionY, Blz::Graphics::Texture texture);
	~Fighter() = default;

	Comp::Transform const GetTransform() const { return transform; };
	void Insert(Comp::Transform newTransform) { transform = newTransform; };

	Comp::SpriteTileSheet const GetSpriteSheet() const { return spriteSheet; };
	void Insert(Comp::SpriteTileSheet newSpriteSheet) { spriteSheet = newSpriteSheet; };

	Comp::Animation const GetAnimation() const { return animation; };
	void Insert(Comp::Animation newAnimation) { animation = newAnimation; };

	Comp::Input GetInput() const { return input; };
	void Insert(Comp::Input newInput) { input = newInput; };

	Comp::Velocity const GetVelocity() const { return velocity; };
	void Insert(Comp::Velocity newVelocity) { velocity = newVelocity; };

	Comp::Position const GetPosition() const { return position; };
	void Insert(Comp::Position newPosition) { position = newPosition; };

	Comp::Movement const GetMovement() const { return movement; };
	void Insert(Comp::Movement newMovement) { movement = newMovement; };

	glm::vec2 originalPosition{ 0.0f, 0.0f };

private:
	//Give Managers direct access to Fighter members for quicker/easier highlevel logic functions
	friend class Blz::Physics::Manager;
	friend class Blz::Input::Manager;
	friend class Blz::Animation::Manager;

	Comp::Transform transform;
	Comp::Velocity velocity;
	Comp::SpriteTileSheet spriteSheet;
	Comp::Animation animation;
	Comp::Position position;
	Comp::Input input;
	Comp::Movement movement;
};
