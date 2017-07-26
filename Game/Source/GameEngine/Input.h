#pragma once
#include "../Universal/UnorderedMap.h"

namespace Blz
{
	enum class GameState
	{
		PLAY,
		EXIT
	};

	class Input
	{
	public:
		Input();
		~Input();

		void ProcessInput();

		void pressKey(uint keyID);
		void releaseKey(uint keyID);

		bool IsKeyPressed(uint keyID);

	private:
		Blz::UMap<uint, bool> keyMap;
		SDL_Event evnt;
	};
}
