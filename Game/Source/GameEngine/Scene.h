#pragma once
#include <GLM\vec2.hpp>
#include "Graphics\Texture.h"
#include "Containers/SmallVector.h"

class Fighter;

namespace Blz { namespace Input { class Engine; }; };
namespace Blz { namespace Animation { class Engine; }; };
namespace Blz { namespace Physics { class Engine; }; };
namespace Blz { namespace Graphics { class Engine; }; };

class Scene
{
public:
	Scene();
	~Scene() = default;

	auto AddFighter(Fighter* fighter) -> void;

	auto SetBackground(Blz::Graphics::Texture backgroundTexture) -> void;

private:
	uint16 numFighters{};
	Blz::SmallVector<Fighter*> fighters{};
	Blz::Graphics::Texture backgroundTexture{};

	friend class Blz::Input::Engine;
	friend class Blz::Animation::Engine;
	friend class Blz::Physics::Engine;
	friend class Blz::Graphics::Engine;
};

