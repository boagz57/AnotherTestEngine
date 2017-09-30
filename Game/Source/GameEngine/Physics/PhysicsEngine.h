#pragma once
#include "../Scene.h"

namespace Blz { namespace Graphics { class Window; }; };

namespace Blz
{
	namespace Physics
	{
		class Engine
		{
		public:
			Engine() = default;
			~Engine() = default;

			auto Move(Fighter* const fighter, const sfloat movementInX, const sfloat movementInY) -> void;
			auto Jump(Fighter* const fighter, const sfloat jumpVelocity) -> void;

			auto Init() -> void;
			auto Shutdown() -> void;
			auto Update(Scene& scene) -> void;
		};
	}
}