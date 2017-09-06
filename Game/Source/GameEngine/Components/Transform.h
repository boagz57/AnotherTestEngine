#pragma once
#include <GLM/vec2.hpp>

namespace Comp
{
	class Transform
	{
	public:
		Transform() = default;

		glm::vec2 const GetCurrentTranslation() const;

		void TranslateBy(sfloat amountToTranslateX, sfloat amountToTranslateY);
		void ZeroOut();

	private:
		glm::vec2 translation{ 0.0f, 0.0f };
		glm::vec2 rotation{ 0.0f, 0.0f };
		glm::vec2 scale{ 0.0f, 0.0f };
	};
}
