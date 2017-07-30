#pragma once
#include "../Universal/SmallVector.h"
#include "Fighter.h"

namespace Blz { namespace Graphics { class Renderer; } }
namespace Blz { class Input; }

class Scene
{
public:
	Scene();
	~Scene();

	Fighter* CreateFighter(Blz::string spriteImageFilePath, uint16 startingWorldPositionX, uint16 startingWorldPositionY);

private:
	friend class Blz::Graphics::Renderer;
	friend class Blz::Input;

	uint16 numFighters = 0;
	Blz::SmallVector<Fighter> fighters;
};

