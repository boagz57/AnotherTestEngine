#pragma once
#include "Fighter.h"

namespace Blz::Animation
{
	class GameLogic
	{
	public:
		static auto CreateAnimation(Fighter* const fighter, const uint16 startingIndex, const uint16 numberOfTilesToAnimate, bool makeDefault = false)->uint16;
		static auto PlayAnimation(Fighter* const fighter, uint16 const animationToPlay) -> void;
	};
}

using BlzAnimation = Blz::Animation::GameLogic;
