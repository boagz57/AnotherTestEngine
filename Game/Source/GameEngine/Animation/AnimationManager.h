#pragma once
#include "Scene.h"

class AnimationManager
{
public:
	AnimationManager() = default;
	~AnimationManager() = default;

	void Init(Scene& scene);
	void Update(Scene& scene);
};

