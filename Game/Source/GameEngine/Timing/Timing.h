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
		auto UpdateTime() -> void;

		auto GetPreviousFrameTime() const -> sfloat { return frameTime; };

	private:
		sfloat frameTime = 0;
		uint32 timePointLastFrame = 0;
	};
}