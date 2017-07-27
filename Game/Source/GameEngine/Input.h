#pragma once
#include "Fighter.h"
#include "../Universal/UnorderedMap.h"

namespace Blz
{
	class Input
	{
	public:
		Input();
		~Input();

		void ProcessInput(Fighter& fighterToApplyInputTo);

		bool IsKeyPressed(uint keyID);

	private:
		Blz::UMap<uint, bool> keyMap;
		SDL_Event evnt;
	};
}
