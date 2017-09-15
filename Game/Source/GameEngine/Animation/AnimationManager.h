#pragma once
#include "Fighter.h"
#include "Graphics/Texture.h"

namespace Blz
{
	namespace Animation
	{
		class Manager
		{
		public:
			//TODO: How to link texture to animation?
			auto CreateAnimation(Fighter* fighter, uint16 startingIndex, uint16 numberOfTilesToAnimate) -> uint16;
			auto PlayAnimation(Fighter* fighter, uint16 const animationToPlay) -> void;
		};
	}
}