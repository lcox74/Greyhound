#pragma once

#include "Core/Window.h"

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
		temp += this->get_delta_time();

		r = std::abs(std::sin(temp) * 25);

		this->draw_rounded_rect(x, y, 50, 50, this->r, { 40, 100, 200 });
		this->draw_rounded_rect(400, 200, 100, 50, this->r, { 40, 200, 100 });

		this->r = r + input->get_interpolated_keys(KEYCODE::Q, KEYCODE::E) * speed * this->get_delta_time();

		this->draw_text("MOUSE:\n    X = " + std::to_string(this->input->get_mouse_x()) +
			"\n    Y = " + std::to_string(this->input->get_mouse_y()) +
			"\n    Mouse Down",
			25.0f, 50.0f, 12, { 255, 255, 255 }, "res/Fonts/OpenSans/OpenSansRegular.ttf");

		if (this->input->get_mouse_button(MOUSEBUTTON::LEFT))
			this->draw_filled_circle(30, 101, 5, { 40, 200, 60 });
		else
			this->draw_filled_circle(30, 101, 5, { 200, 40, 100 });

		this->draw_circle(30, 101, 5, { 0, 0, 0 });

		this->draw_text("FPS: " + std::to_string(this->get_frame_rate_smooth()), 600, 50, 12, { 255, 255, 255 });

		if (this->input->get_key({ KEYCODE::W, KEYCODE::UP }))
			this->draw_filled_triangle(600, 322, 568, 378, 632, 378, { 40, 200, 40 }); // Up
		else
			this->draw_filled_triangle(600, 322, 568, 378, 632, 378, { 100, 100, 100 }); // Up

		if (this->input->get_key({ KEYCODE::S, KEYCODE::DOWN }))
			this->draw_filled_triangle(568, 464, 600, 514, 632, 464, { 40, 200, 40 }); // Down
		else
			this->draw_filled_triangle(568, 464, 600, 514, 632, 464, { 100, 100, 100 }); // Down

		if (this->input->get_key({ KEYCODE::A, KEYCODE::LEFT }))
			this->draw_filled_triangle(556, 390, 500, 420, 556, 452, { 40, 200, 40 }); // Left
		else
			this->draw_filled_triangle(556, 390, 500, 420, 556, 452, { 100, 100, 100 }); // Left

		if (this->input->get_key({ KEYCODE::D, KEYCODE::RIGHT }))
			this->draw_filled_triangle(644, 390, 644, 452, 698, 420, { 40, 200, 40 }); // Right
		else
			this->draw_filled_triangle(644, 390, 644, 452, 698, 420, { 100, 100, 100 }); // Right

		int horizontal = input->get_interpolated_keys({ KEYCODE::A, KEYCODE::LEFT }, { KEYCODE::D, KEYCODE::RIGHT });
		int vertical = input->get_interpolated_keys({ KEYCODE::W, KEYCODE::UP }, { KEYCODE::S, KEYCODE::DOWN });

		float newX = (float)horizontal;
		float newY = (float)vertical;

		if (horizontal != 0 && vertical != 0) {
			newX /= std::sqrtf(2);
			newY /= std::sqrtf(2);
		}

		x += speed * this->get_delta_time() * newX;
		y += speed * this->get_delta_time() * newY;


		this->draw_line(600, 420, 600 + (35 * newX), 420 + (35 * newY), { 255, 255, 30 }, 2);

		this->draw_filled_circle(600, 420, 3, { 100, 100, 100 });
		this->draw_circle(600, 420, 35, { 100, 100, 100 });
	}

	bool first;
	float x = 250, y = 100, r = 5;
	float speed = 60;
	float temp = 0;
};

