#pragma once
#include <GLM/vec2.hpp>

namespace Comp
{
	class Transform
	{
	public:
		Transform() = default;

		glm::vec2 const GetCurrentTranslation() const;

		void TranslateBy(const sfloat amountToTranslateX, const sfloat amountToTranslateY);
		void ZeroOut();

	private:
		glm::vec2 translation{};
		glm::vec2 rotation{};
		glm::vec2 scale{};
	};
}
