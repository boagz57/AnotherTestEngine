#pragma once
#include <SDL.h>

namespace Blz
{
	namespace Timing
	{
		//Should be placed at very end of game loop
		void CalculateAndDisplayFPS();

		class EngineClock
		{
		public:
			void Init();
			void UpdateTime();

			uint32 const GetDeltaTime() const { return deltaTime; };

		private:
			uint32 deltaTime = 0;
			uint32 timePointLastFrame = 0;
		};
	}
}