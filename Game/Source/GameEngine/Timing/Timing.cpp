#include <SDL.h>
#include "Timing.h"

namespace Blz
{
	namespace Timing
	{
		auto CalculateAndDisplayFPS() -> void
		{
			static sfloat FPS = 0.0f;
			static uint32 frames = 0;
			static bool firstTimeCalculatingFPS = true;
			static uint32 startTime = 0;

			//Setup timing variables on first call of function
			if (firstTimeCalculatingFPS)
			{
				frames = 0;
				startTime = SDL_GetTicks();
				firstTimeCalculatingFPS = false;
			}

			frames++;

			//Only display FPS after so many milliseconds
			if (SDL_GetTicks() - startTime > 250 && frames > 10)
			{
				FPS = static_cast<sfloat>((frames / (.001 * (SDL_GetTicks() - startTime))));
				startTime = SDL_GetTicks();
				frames = 0;
				LOG("FPS: %f\n", FPS);
			}
		}

		auto EngineClock::Init() -> void
		{
			timePointLastFrame = SDL_GetTicks();
		}

		auto EngineClock::UpdateTime() -> void
		{
			auto timePointThisFrame = SDL_GetTicks();
			auto timeDifference = timePointThisFrame - timePointLastFrame;
			frameTime = (static_cast<sfloat>(timeDifference) * .001f);
			timePointLastFrame = timePointThisFrame;
		}
	}
}

Blz::Timing::EngineClock engineClock;