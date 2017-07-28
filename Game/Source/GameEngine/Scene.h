#pragma once
#include "Fighter.h"

namespace Blz { namespace Graphics { class Renderer; } }
namespace Blz { class Input; }

class Scene
{
public:
	Scene();
	~Scene();

	void AddFighterToScene(Fighter& fighterToAdd);

	Blz::Vector<Fighter> fighters;
};

