#pragma once

#include <vector>
#include <memory>
#include <chrono>

#include "../GH_Input.h"
#include "../GH_Graphics.h"
#include "GH_UI_Element.h"

class GH_UI
{
public:
	GH_UI(GH_Graphics* g, GH_Input* i) { this->graphics = g; this->input = i; }
	~GH_UI() {}
	
	void update() {
		for (int i = 0; i < (int)elements.size(); i++) {
			elements[i]->Update();
			if (!elements[i]->isEnabled()) elements[i]->OnDisable();
			if (elements[i]->isInBounds(this->input->get_mouse())) {
				elements[i]->OnHover();

				if (this->input->get_mouse_button_down(MOUSEBUTTON::LEFT) || this->input->get_mouse_button_down(MOUSEBUTTON::MIDDLE) || this->input->get_mouse_button_down(MOUSEBUTTON::RIGHT))
					elements[i]->OnClick();

				if (this->input->get_mouse_button(MOUSEBUTTON::LEFT) || this->input->get_mouse_button(MOUSEBUTTON::MIDDLE) || this->input->get_mouse_button(MOUSEBUTTON::RIGHT))
					elements[i]->OnDrag();
			}
		}
	}

	void addComponent(GH_UI_Element* e) { e->setGraphics(this->graphics); e->setInput(this->input);  this->elements.push_back(e); }

private:
	std::vector<GH_UI_Element*> elements;
	GH_Graphics* graphics;
	GH_Input* input;
};