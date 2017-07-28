#pragma once
#include "Fighter.h"

namespace Blz { namespace Graphics { class Renderer; } }
namespace Blz { class Input; }

class Scene
{
public:
	Scene();
	~Scene();

	Fighter* CreateFighter();

private:
	friend class Blz::Graphics::Renderer;
	friend class Blz::Input;

	uint16 numFighters = 0;
	Blz::Vector<Fighter> fighters;
};

