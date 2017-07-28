#pragma once
#include "Graphics/Window.h"
#include "Graphics/Renderer.h"
#include "Scene.h"
#include "Game.h"

class Engine
{
public:
	Engine();
	~Engine();

	void Init();

	void GameLoop(Scene& scene, Game& game);

private:
	Blz::Window window;
	Blz::Graphics::Renderer renderer;

};

