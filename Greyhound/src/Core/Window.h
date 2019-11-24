#pragma once

#include <iostream>
#include <string>
#include <map>
#include <math.h>
#include <vector>
#include <numeric>
#include <initializer_list>

#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>
#include FT_FREETYPE_H 

#include <SDL.h>
#include <SDL_ttf.h>
#undef main

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

#include "GH_Input.h"

struct font_data {
	float height;
	std::vector<GLuint> textures;
	GLuint list_base;
};

class Window
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

	GH_Input* input;

	float get_delta_time();
	float get_delta_time_smooth();

	int get_frame_rate();
	int get_frame_rate_smooth();

	int get_max_frame_rate();
	void set_max_frame_rate(int max);

public: // Draw Calls

	void set_clear_colour(SDL_Color color);

	void draw_rounded_rect(float x, float y, float w, float h, float r, SDL_Color color);
	void draw_filled_rect(float x, float y, float w, float h, SDL_Color color);
	void draw_rect(float x, float y, float w, float h, SDL_Color color);

	void draw_filled_quad(float x1, float y1, float x2, float y2, SDL_Color color);
	void draw_filled_quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, SDL_Color color);
	void draw_quad(float x1, float y1, float x2, float y2, SDL_Color color);
	void draw_quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, SDL_Color color);

	void draw_filled_triangle(float x1, float y1, float x2, float y2, float x3, float y3, SDL_Color color);
	void draw_triangle(float x1, float y1, float x2, float y2, float x3, float y3, SDL_Color color);

	void draw_filled_circle(float x, float y, float r, SDL_Color color);
	void draw_circle(float x, float y, float r, SDL_Color color);

	void draw_text(std::string text, float x, float y, int size, SDL_Color color, std::string fontfamily = "res/Fonts/Arial/arial.ttf", float linespace = 1.5873f);
	void draw_line(float x1, float y1, float x2, float y2, SDL_Color color, float thickness = 1);

	float get_relative_x(float x);
	float get_relative_y(float y);
	
private:
	std::map<const char*, font_data> fonts;

	font_data text_init(std::string font, int size);
	void text_make_textures(FT_Face face, char ch, GLuint list_base, GLuint* tex_base);

	void draw_shape(GLfloat* verts, int vertCount, GLuint* indecies, int indeCount, int drawMode = GL_TRIANGLES);

	Shader* shapeShader = nullptr;
	Shader* circleShader = nullptr;
	Shader* textShader = nullptr;

	std::vector<double> frame_list = std::vector<double>();
	int frame_smooth = 100;
	Uint32 frame_now = SDL_GetTicks();
	Uint32 frame_last = 0;
	double delta_time = 0;
	int frame_rate_max = 60;
};

