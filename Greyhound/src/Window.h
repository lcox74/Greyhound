#pragma once

#include <iostream>
#include <string>
#include <map>
#include <math.h>
#include <vector>

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

struct font_data {
	float height;
	std::vector<GLuint> textures;
	GLuint list_base;
};

struct point {
	GLfloat x;
	GLfloat y;
	GLfloat s;
	GLfloat t;
};

class Window
{
public:

	int window_loop();

	virtual void Render() = 0;

	int width, height;
	std::string name;
	bool bfullscreen;

	SDL_Window* sdl_window = nullptr;
	SDL_GLContext gl_context;
	SDL_Event sdl_event;

	void init(std::string name, int width, int height, bool bfullscreen);

	GLuint VAO = 0, VBO = 0, IBO = 0;
	FT_Library ft;
	FT_Face face;

	void draw_rect(float x, float y, float w, float h, SDL_Color color);
	void draw_quad(float x1, float y1, float x2, float y2, SDL_Color color);
	void draw_quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, SDL_Color color);
	void draw_triangle(float x1, float y1, float x2, float y2, float x3, float y3, SDL_Color color);
	void draw_circle(float x, float y, float r, SDL_Color color);
	void draw_text(std::string text, float x, float y, float size, SDL_Color color, std::string fontfamily = "res/Fonts/Arial/arial.ttf", float linespace = 1.5873f);
	void draw_line(float x1, float y1, float x2, float y2, SDL_Color color, float thickness = 1);

	float get_relative_x(float x);
	float get_relative_y(float y);

	void clean();

	
private:
	std::map<const char*, font_data> fonts;

	font_data text_init(std::string font, int size);
	void text_make_textures(FT_Face face, char ch, GLuint list_base, GLuint* tex_base);

	void basic_shape_shader(GLfloat* verts, int vertCount, GLuint* indecies, int indeCount);
	void circle_shape_shader(GLfloat* verts, int vertCount, GLuint* indecies, int indeCount);

	Shader* shapeShader = nullptr;
	Shader* circleShader = nullptr;
	Shader* textShader = nullptr;
};

