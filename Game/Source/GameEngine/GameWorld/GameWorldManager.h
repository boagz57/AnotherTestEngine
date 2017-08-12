#pragma once
#include "../Scene.h"

namespace Blz
{
	namespace GameWorld
	{
		class GameWorldManager
		{
		public:
			GameWorldManager();
			~GameWorldManager();

			void Init(Scene& scene);
			void Update(Scene& scene);
		};
	}
}