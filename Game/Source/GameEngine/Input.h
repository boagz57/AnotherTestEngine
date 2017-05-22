#pragma once
#include "../Universal/UnorderedMap.h"

namespace Blz
{
	class Input
	{
	public:
		Input();
		~Input();

		static void pressKey(uint keyID);
		static void releaseKey(uint keyID);

		static bool IsKeyPressed(uint keyID);

	private:
		static Blz::UMap<uint, bool> keyMap;
	};
}
