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

			uint32 const GetFrameTime() const { return frameTime; };

		private:
			uint32 frameTime = 0;
			uint32 timePointLastFrame = 0;
		};
	}
}