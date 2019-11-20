#include "GameView.h"

// Window and fullscreen of determined resolution
GameView::GameView(std::string name, int width, int height, bool bfullscreen)
{
	this->init(name, width, height, bfullscreen);
}

// Fullscreen full resolution of display
GameView::GameView(std::string name, bool bfullscreen, int display)
{
	SDL_DisplayMode current;
	SDL_GetCurrentDisplayMode(display, &current);

	this->width = current.w;
	this->height = current.h;

	this->init(name, this->width, this->height, bfullscreen);

	this->first = false;
}

GameView::~GameView() { this->clean(); }

void GameView::Render() 
{

	this->draw_text("Hello, World!\nAlso multiline!", 25.0f, 25.0f, 12, { 255, 255, 255 });
	this->draw_rect(100, 100, 50, 50, { 40, 100, 200 });

	this->draw_triangle(100, 10, 150, 300, 170, 200, { 40, 200, 100 });
	
	this->draw_quad(100, 100, 100, 150, 150, 150, 150, 100, { 40, 100, 200 });

	this->draw_circle(550, 400, 30, { 200, 40, 100 });

	this->draw_line(100, 400, 150, 200, { 255, 60, 10 }, 1);


}