#pragma once

#include "../GH_Input.h"
#include "../GH_Graphics.h"

#include <string>

class GH_UI_Element
{
public:
	
	virtual void OnClick() {}
	virtual void OnDrag() {}
	virtual void OnHover() {}
	virtual void OnDisable() {}
	virtual void Update() {}

	bool isEnabled() { return this->enabled; }
	bool setEnabled(bool state) { return this->enabled = state; }

	bool isInBounds(float x1, float y1) 
	{
		return (x1 >= this->x && x1 <= this->x + this->w) && 
			   (y1 >= this->y && y1 <= this->y + this->h);
	}

	bool isInBounds(glm::vec2 pos)
	{
		return (pos.x >= this->x && pos.x <= this->x + this->w) &&
			(pos.y >= this->y && pos.y <= this->y + this->h);
	}

	bool hasTag(std::string objectTag) { return (objectTag == this->tag); }
	void setTag(std::string objectTag) { this->tag = objectTag; }

	void setGraphics(GH_Graphics* g) { this->graphics = g; }
	GH_Graphics* getGraphics() { return this->graphics; }

	void setInput(GH_Input* i) { this->input = i; }
	GH_Input* getInput() { return this->input; }
	
	float x, y, w, h;

private:
	std::string tag;
	bool enabled = true;
	GH_Graphics* graphics;
	GH_Input* input;
};