#pragma once

#include <iostream>
#include <string>
#include <map>
#include <math.h>
#include <vector>
#include <numeric>
#include <initializer_list>
#include <fstream>

#include <SDL.h>
#include <SDL_ttf.h>
#undef main

#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>
#include FT_FREETYPE_H 

// OpenGL Headers
#include <windows.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL_opengl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Asserts.h"
#include "Shader.h"

#include "GH_Graphics.h"
#include "GH_Input.h"
#include "UI/GH_UI.h"


class GH_Window
{
public:
	int window_loop();

	virtual void Update() = 0;

	int width = 0, height = 0;
	std::string name;
	bool bfullscreen;

	SDL_Window* sdl_window = nullptr;
	SDL_GLContext gl_context;
	SDL_Event sdl_event;

	void init(std::string name, int width, int height, bool bfullscreen);
	void clean();

	GLuint VAO = 0, VBO = 0, IBO = 0;
	FT_Library ft;
	FT_Face face;

	GH_Graphics* graphics;
	GH_Input* input;
	GH_UI* ui;

	void set_window_borderless();
	void set_window_bordered();

	float get_delta_time();
	float get_delta_time_smooth();

	int get_frame_rate();
	int get_frame_rate_smooth();

	int get_max_frame_rate();
	void set_max_frame_rate(int max);

	void toggle_pause_window() { this->pause_window = !this->pause_window; }
	
private:
	std::vector<double> frame_list = std::vector<double>();
	int frame_smooth = 100;
	Uint32 frame_now = SDL_GetTicks();
	Uint32 frame_last = 0;
	double delta_time = 0;
	int frame_rate_max = 60;
	bool pause_window = false;

	DWORD pid = GetCurrentProcessId();
};

