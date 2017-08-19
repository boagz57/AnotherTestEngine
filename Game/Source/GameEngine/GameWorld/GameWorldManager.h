#pragma once
#include "../Scene.h"

namespace Blz
{
	namespace GameWorld
	{
		class GameWorldManager
		{
		public:
			GameWorldManager() = default;
			~GameWorldManager() = default;

			void Init(Scene& scene);
			void Update(Scene& scene);
		};
	}
}