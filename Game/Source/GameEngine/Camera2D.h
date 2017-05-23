#pragma once
#include <GLM/glm.hpp>

namespace Blz
{
	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void Init(int32 screenWidth, int32 screenHeight);

		void Update();

		void SetPosition(const glm::vec2 newPosition);
		void SetScale(sfloat newScale);

		glm::vec2 GetPosition() { return position; };
		sfloat GetScale() { return scale; };
		glm::mat4 GetTransformationMatrix() { return transformationMatrix; };

	private:
		int32 screenWidth = 500, screenHeight = 500;

		bool cameraNeedsUpdated = true;

		sfloat scale = 1.0f;

		glm::vec2 position{ 0.0f, 0.0f };

		//Initialize matrices to identity matrix
		glm::mat4 transformationMatrix{ 1.0f };
		glm::mat4 orthoMatrix{ 1.0f };
	};
}