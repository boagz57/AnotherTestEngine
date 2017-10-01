#pragma once
#include "Containers/Vector.h"
#include "Scene.h"

namespace Blz
{
	namespace Animation
	{
		class Engine
		{
		public:
			Engine() = default;
			~Engine() = default;

			auto CreateAnimation(Fighter* const fighter, const uint16 startingIndex, const uint16 numberOfTilesToAnimate, bool makeDefault = false)->uint16;
			auto PlayAnimation(Fighter* const fighter, uint16 const animationToPlay) -> void;

			auto Init(Scene& scene) -> void;
			auto Update(Scene& scene) -> void;
		};
	}
}
