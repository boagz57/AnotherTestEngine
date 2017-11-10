#pragma once
#include <SDL.h>

namespace Blz::Timing
{
	//Should be placed at very end of game loop
	void CalculateAndDisplayFPS();

	class EngineClock
	{
	public:
		auto Init() -> void;
		auto CalculatePreviousFrameTime() -> float;

		auto GetPreviousFrameTime() const -> float { return frameTime; };

	private:
		float frameTime = 0;
		unsigned int timePointLastFrame = 0;
	};
}