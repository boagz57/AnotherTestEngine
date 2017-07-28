#pragma once
#include "Scene.h"
#include "../Universal/UnorderedMap.h"

namespace Blz
{
	class Input
	{
	public:
		Input();
		~Input();

		void ProcessInput(Scene& sceneToAppyInputCommandsOn);

		bool IsKeyPressed(uint keyID);

	private:
		Blz::UMap<uint, bool> keyMap;
		SDL_Event evnt;
	};
}
