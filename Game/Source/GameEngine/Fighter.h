#pragma once
#include <GLM/vec2.hpp>
#include "Graphics/Texture.h"
#include "Containers/Map.h"
#include "Components/Animation.h"
#include "Components\Movement.h"
#include "Components/SpriteSheet.h"
#include "Components/Velocity.h"
#include "Components/Input.h"
#include "Components/Transform.h"
#include "Components\Position.h"

namespace Blz { namespace Input { class Engine; }; };
namespace Blz { namespace Graphics { class Engine; }; };
namespace Blz { namespace Animation { class Engine; }; };
namespace Blz { namespace Physics { class Engine; }; };

namespace Blz { namespace Physics { class GameLogic; }; };
namespace Blz { namespace Input { class GameLogic; }; };

class Fighter 
{
public:
	Fighter() = default;

	void Init(sfloat startingWorldPositionX, sfloat startingWorldPositionY, Blz::Graphics::Texture texture);

	glm::vec2 originalPosition{ 0.0f, 0.0f };

protected:
	Comp::Transform const GetTransform() const { return transform; };
	Comp::SpriteSheet const GetSpriteSheet() const { return spriteSheet; };
	Comp::Animation const GetAnimation() const { return animation; };
	Comp::Input GetInput() const { return input; };
	Comp::Velocity const GetVelocity() const { return velocity; };
	Comp::Position const GetPosition() const { return position; };
	Comp::Movement const GetMovement() const { return movement; };

private:
	friend class Blz::Graphics::Engine;
	friend class Blz::Input::Engine;
	friend class Blz::Animation::Engine;
	friend class Blz::Physics::Engine;

	friend class Blz::Physics::GameLogic;
	friend class Blz::Input::GameLogic;

	Comp::Transform transform;
	Comp::Velocity velocity;
	Comp::SpriteSheet spriteSheet;
	Comp::Animation animation;
	Comp::Position position;
	Comp::Input input;
	Comp::Movement movement;
};
