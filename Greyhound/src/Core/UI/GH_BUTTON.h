#pragma once

#include <SDL.h>
#include "GH_UI_Element.h"

class GH_BUTTON : public GH_UI_Element
{
public:
	GH_BUTTON(float posx, float posy, float width, float height) {
		this->x = posx;
		this->y = posy;
		this->w = width;
		this->h = height;
	}
	~GH_BUTTON() { }

	void Update()
	{	
		this->getGraphics()->draw_rounded_rect(this->x, this->y, this->w, this->h, 5, { 40, 167, 69 });
		this->getGraphics()->draw_text("OK", this->x + (this->w / 2.0f) - 10, this->y + (this->h / 2.0f) + 8, 12, { 255, 255, 255 });
	}

	void OnHover()
	{
		this->getGraphics()->draw_rounded_rect(this->x, this->y, this->w, this->h, 5, { 37, 155, 64 });
		this->getGraphics()->draw_text("OK", this->x + (this->w / 2.0f) - 10, this->y + (this->h / 2.0f) + 8, 12, { 255, 255, 255 });

	}

	void OnClick()
	{
		this->getGraphics()->draw_rounded_rect(this->x, this->y, this->w, this->h, 5, { 35, 144, 60 });
		this->getGraphics()->draw_text("OK", this->x + (this->w / 2.0f) - 10, this->y + (this->h / 2.0f) + 8, 12, { 255, 255, 255 });

	}

	void OnDrag()
	{
		this->getGraphics()->draw_rounded_rect(this->x, this->y, this->w, this->h, 5, { 35, 144, 60 });
		this->getGraphics()->draw_text("OK", this->x + (this->w / 2.0f) - 10, this->y + (this->h / 2.0f) + 8, 12, { 255, 255, 255 });

	}
};
