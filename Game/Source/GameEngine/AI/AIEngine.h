#pragma once

class Scene;

namespace Blz::AI
{
	class Engine
	{
	public:
		Engine() = default;
		~Engine() = default;

		void Init();
		void Shutdown();

		void Update(Scene& scene);
	};
}
