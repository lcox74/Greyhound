#pragma once

#include "Window.h"

class GameView : public Window
{
public:
	GameView(std::string name, int width = 800, int height = 600, bool bfullscreen = false);
	GameView(std::string name, bool bfullscreen, int display = 0);
	~GameView();

	void Render();

	bool first;
};

