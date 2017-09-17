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
			auto CreateAnimation(Fighter* const fighter, const uint16 startingIndex, const uint16 numberOfTilesToAnimate) -> uint16;
			auto PlayAnimation(Fighter* const fighter, uint16 const animationToPlay) -> void;
		};
	}
}