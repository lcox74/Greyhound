#pragma once

#include "Window.h"

class GameView : public Window
{
public:
	GameView(std::string name, int width = 800, int height = 600, bool bfullscreen = false) { this->init(name, width, height, bfullscreen); }
	GameView(std::string name, bool bfullscreen, int display = 0) 
	{
		SDL_DisplayMode current;
		SDL_GetCurrentDisplayMode(display, &current);

		this->width = current.w;
		this->height = current.h;

		this->init(name, this->width, this->height, bfullscreen);

		this->first = false;
	}

	~GameView() { this->clean(); }

	void Update()
	{
		this->draw_text("Hello, World!\nAlso multiline!", 25.0f, 50.0f, 12, { 255, 255, 255 });

		if (this->get_key(KEYCODE::W)) y -= speed * 1 / 60;
		if (this->get_key(KEYCODE::S)) y += speed * 1 / 60;
		if (this->get_key(KEYCODE::A)) x -= speed * 1 / 60;
		if (this->get_key(KEYCODE::D)) x += speed * 1 / 60;

		this->draw_filled_rect(x, y, 50, 50, { 40, 100, 200 });

		this->draw_triangle(700, 50, 500, 100, 550, 120, { 40, 200, 100 });

		this->draw_quad(300, 250, 350, 300, 400, 250, 350, 200, { 40, 100, 100 });

		this->draw_circle(550, 400, 30, { 200, 40, 100 });

		this->draw_line(100, 400, 150, 200, { 255, 60, 10 }, 1);
		this->draw_line(200, 400, 250, 200, { 255, 60, 10 }, 5);
	}

	bool first;
	float x = 250, y = 100;
	float speed = 90;
};

