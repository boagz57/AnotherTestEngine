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

		void SetPosition(const glm::vec2 newPosition) { position = newPosition; cameraNeedsUpdated = true; };
		void SetScale(sfloat newScale) { scale = newScale; cameraNeedsUpdated = true; };

		glm::vec2 GetPosition() { return position; };
		sfloat GetScale() { return scale; };
		glm::mat4 GetOrthoMatrix() { return transformationMatrix; };

	private:
		int32 screenWidth, screenHeight;
		bool cameraNeedsUpdated;
		sfloat scale;
		glm::vec2 position;
		glm::mat4 transformationMatrix;
		glm::mat4 orthoMatrix;
	};
}