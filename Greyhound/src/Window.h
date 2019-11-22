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

struct key_event {
	Uint8 state = 0;
};

enum class KEYCODE {
	// NUMBERS
	ALPHA0 = SDLK_0, ALPHA1 = SDLK_1, ALPHA2 = SDLK_2, ALPHA3 = SDLK_3, ALPHA4 = SDLK_4,
	ALPHA5 = SDLK_5, ALPHA6 = SDLK_6, ALPHA7 = SDLK_7, ALPHA8 = SDLK_8, ALPHA9 = SDLK_9,

	// ALPHABET
	A = SDLK_a, B = SDLK_b, C = SDLK_c, D = SDLK_d, E = SDLK_e, F = SDLK_f, G = SDLK_g,
	H = SDLK_h, I = SDLK_i, J = SDLK_j, K = SDLK_k, L = SDLK_l, M = SDLK_m, N = SDLK_n,
	O = SDLK_o, P = SDLK_p, Q = SDLK_q, R = SDLK_r, S = SDLK_s, T = SDLK_t, U = SDLK_u,
	V = SDLK_v, W = SDLK_w, X = SDLK_x, Y = SDLK_y, Z = SDLK_z,

	// ARROWS
	UP = SDLK_UP, DOWN = SDLK_DOWN, LEFT = SDLK_LEFT, RIGHT = SDLK_RIGHT,

	// COMMANDS
	LALT = SDLK_LALT, LCRTL = SDLK_LCTRL, LSHIFT = SDLK_LSHIFT, LCOMMAND = SDLK_LGUI,
	RALT = SDLK_RALT, RCRTL = SDLK_RCTRL, RSHIFT = SDLK_RSHIFT, RCOMMAND = SDLK_RGUI,

	RETURN = SDLK_RETURN, PAGEUP = SDLK_PAGEUP, PAGEDOWN = SDLK_PAGEDOWN, TAB = SDLK_TAB,
	PRINTSCREEN = SDLK_PRINTSCREEN, INSERT = SDLK_INSERT, HOME = SDLK_HOME, END = SDLK_END,
	CAPSLOCK = SDLK_CAPSLOCK, BACKSPACE = SDLK_BACKSPACE, DEL = SDLK_DELETE,

	// SPECIALS
	QUOTE = SDLK_QUOTE, COMMA = SDLK_COMMA, EQUALS = SDLK_EQUALS, LBRACKET = SDLK_LEFTBRACKET,
	MINUS = SDLK_MINUS, PERIOD = SDLK_PERIOD, RBRACKET = SDLK_RIGHTBRACKET, SEMICOLON = SDLK_SEMICOLON,
	FORWARDSLASH = SDLK_SLASH, BACKSLASH = SDLK_BACKSLASH, AMPERSAND = SDLK_AMPERSAND,
	ASTERISK = SDLK_ASTERISK, AT = SDLK_AT, CARET = SDLK_CARET, COLON = SDLK_COLON,
	DOLLAR = SDLK_DOLLAR, EXCLAIM = SDLK_EXCLAIM, GREATER = SDLK_GREATER, HASH = SDLK_HASH,
	LPAREN = SDLK_LEFTPAREN, LESS = SDLK_LESS, PERCENT = SDLK_PERCENT, PLUS = SDLK_PLUS,
	QUESTION = SDLK_QUESTION, DQUOTE = SDLK_QUOTEDBL, RPAREN = SDLK_RIGHTPAREN, UNDERSCORE = SDLK_UNDERSCORE,

	// FUNCTIONS
	F1 = SDLK_F1, F2 = SDLK_F2, F3 = SDLK_F3, F4 = SDLK_F4, F5 = SDLK_F5, F6 = SDLK_F6, F7 = SDLK_F7, 
	F8 = SDLK_F8, F9 = SDLK_F9, F10 = SDLK_F10, F11 = SDLK_F11, F12 = SDLK_F12, F13 = SDLK_F13,
	F14 = SDLK_F14, F15 = SDLK_F15, F16 = SDLK_F16, F17 = SDLK_F17, F18 = SDLK_F18, F19 = SDLK_F19, F20 = SDLK_F20,
	F21 = SDLK_F21, F22 = SDLK_F22, F23 = SDLK_F23, F24 = SDLK_F24
};

class Window
{
public:

	int window_loop();

	virtual void Update() = 0;

	int width, height;
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

public: // Key Events
	bool get_key(KEYCODE key); // If Key is Down + Held
	bool get_key_down(KEYCODE key); // If Key Just Pressed
	bool get_key_up(KEYCODE key); // If Key Just Released

public: // Draw Calls

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

	std::map<KEYCODE, key_event> keys;

	font_data text_init(std::string font, int size);
	void text_make_textures(FT_Face face, char ch, GLuint list_base, GLuint* tex_base);

	void key_init();

	void basic_filled_shape_shader(GLfloat* verts, int vertCount, GLuint* indecies, int indeCount);
	void basic_shape_shader(GLfloat* verts, int vertCount, GLuint* indecies, int indeCount);
	void circle_shape_shader(GLfloat* verts, int vertCount, GLuint* indecies, int indeCount);

	Shader* shapeShader = nullptr;
	Shader* circleShader = nullptr;
	Shader* textShader = nullptr;
};

