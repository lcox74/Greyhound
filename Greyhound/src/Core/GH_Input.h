#pragma once

#include <iostream>
#include <map>
#include <memory>

#include <glm/glm.hpp>

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

enum class MOUSEBUTTON {
	LEFT = SDL_BUTTON_LEFT,
	MIDDLE = SDL_BUTTON_MIDDLE,
	RIGHT = SDL_BUTTON_RIGHT
};

class GH_Input {
	struct key_event {
		Uint8 state = 0;
	};

	std::map<KEYCODE, key_event> key_states;
	std::map<MOUSEBUTTON, key_event> mouse_states;
	
	glm::vec2 mouse_position;

public:
	GH_Input() {
		KEYCODE* all_keys = new KEYCODE[110]{
			// NUMBERS
			KEYCODE::ALPHA0, KEYCODE::ALPHA1, KEYCODE::ALPHA2, KEYCODE::ALPHA3, KEYCODE::ALPHA4,
			KEYCODE::ALPHA5, KEYCODE::ALPHA6, KEYCODE::ALPHA7, KEYCODE::ALPHA8, KEYCODE::ALPHA9,

			KEYCODE::A, KEYCODE::B, KEYCODE::C, KEYCODE::D, KEYCODE::E, KEYCODE::F, KEYCODE::G,
			KEYCODE::H, KEYCODE::I, KEYCODE::J, KEYCODE::K, KEYCODE::L, KEYCODE::M, KEYCODE::N,
			KEYCODE::O, KEYCODE::P, KEYCODE::Q, KEYCODE::R, KEYCODE::S, KEYCODE::T, KEYCODE::U,
			KEYCODE::V, KEYCODE::W, KEYCODE::X, KEYCODE::Y, KEYCODE::Z,

			KEYCODE::UP, KEYCODE::DOWN, KEYCODE::LEFT, KEYCODE::RIGHT,

			// COMMANDS
			KEYCODE::LALT, KEYCODE::LCRTL, KEYCODE::LSHIFT, KEYCODE::LCOMMAND,
			KEYCODE::RALT, KEYCODE::RCRTL, KEYCODE::RSHIFT, KEYCODE::RCOMMAND,

			KEYCODE::RETURN, KEYCODE::PAGEUP, KEYCODE::PAGEDOWN, KEYCODE::TAB,
			KEYCODE::PRINTSCREEN, KEYCODE::INSERT, KEYCODE::HOME, KEYCODE::END,
			KEYCODE::CAPSLOCK, KEYCODE::BACKSPACE, KEYCODE::DEL,

			// SPECIALS
			KEYCODE::QUOTE, KEYCODE::COMMA, KEYCODE::EQUALS, KEYCODE::LBRACKET,
			KEYCODE::MINUS, KEYCODE::PERIOD, KEYCODE::RBRACKET, KEYCODE::SEMICOLON,
			KEYCODE::FORWARDSLASH, KEYCODE::BACKSLASH, KEYCODE::AMPERSAND,
			KEYCODE::ASTERISK, KEYCODE::AT, KEYCODE::CARET, KEYCODE::COLON,
			KEYCODE::DOLLAR, KEYCODE::EXCLAIM, KEYCODE::GREATER, KEYCODE::HASH,
			KEYCODE::LPAREN, KEYCODE::LESS, KEYCODE::PERCENT, KEYCODE::PLUS,
			KEYCODE::QUESTION, KEYCODE::DQUOTE, KEYCODE::RPAREN, KEYCODE::UNDERSCORE,

			// FUNCTIONS
			KEYCODE::F1, KEYCODE::F2, KEYCODE::F3, KEYCODE::F4, KEYCODE::F5,
			KEYCODE::F6, KEYCODE::F7, KEYCODE::F8, KEYCODE::F9, KEYCODE::F10,
			KEYCODE::F11, KEYCODE::F12, KEYCODE::F13, KEYCODE::F14, KEYCODE::F15,
			KEYCODE::F16, KEYCODE::F17, KEYCODE::F18, KEYCODE::F19, KEYCODE::F20,
			KEYCODE::F21, KEYCODE::F22, KEYCODE::F23, KEYCODE::F24
		};

		MOUSEBUTTON* all_btns = new MOUSEBUTTON[3]{
			MOUSEBUTTON::LEFT, MOUSEBUTTON::MIDDLE, MOUSEBUTTON::RIGHT
		};

		key_event empty = { 0 };

		for (int i = 0; i < 110; i++) this->key_states.insert(std::pair<KEYCODE, key_event>(all_keys[i], empty));
		for (int i = 0; i < 3; i++) this->mouse_states.insert(std::pair<MOUSEBUTTON, key_event>(all_btns[i], empty));

		this->mouse_position = glm::vec2(0);

		delete[] all_keys;
		delete[] all_btns;
	}

	~GH_Input() { }

	void input_update() {
		// Key Setting
		std::map<KEYCODE, key_event>::iterator keys;
		for (keys = this->key_states.begin(); keys != this->key_states.end(); keys++) {
			if (keys->second.state == 1)
				keys->second.state = 0;

			if (keys->second.state == 2)
				keys->second.state = 3;
		}

		// Mouse Setting
		std::map<MOUSEBUTTON, key_event>::iterator mouse;
		for (mouse = this->mouse_states.begin(); mouse != this->mouse_states.end(); mouse++) {
			if (mouse->second.state == 1)
				mouse->second.state = 0;

			if (mouse->second.state == 2)
				mouse->second.state = 3;
		}
	}

	void update_key(KEYCODE key, int state) { this->key_states[key].state = state; }
	void update_button(MOUSEBUTTON key, int state) { this->mouse_states[key].state = state; }
	void update_mouse_position(int x, int y) { this->mouse_position = glm::vec2(x, y); }

	bool get_key(KEYCODE key) { return (this->key_states[key].state > 1); }
	bool get_key_down(KEYCODE key) { return (this->key_states[key].state == 2); }
	bool get_key_up(KEYCODE key) { return (this->key_states[key].state == 1); }

	bool get_key(std::initializer_list<KEYCODE> keys)
	{
		for (auto key : keys) if (this->key_states[key].state > 1) return true;
		return false;
	}

	bool get_key_down(std::initializer_list<KEYCODE> keys)
	{
		for (auto key : keys) if (this->key_states[key].state == 2) return true;
		return false;
	}

	bool get_key_up(std::initializer_list<KEYCODE> keys)
	{
		for (auto key : keys) if (this->key_states[key].state == 1) return true;
		return false;
	}

	bool get_mouse_button(MOUSEBUTTON btn) { return (this->mouse_states[btn].state > 1); }

	bool get_mouse_button_down(MOUSEBUTTON btn) { return (this->mouse_states[btn].state == 2); }

	bool get_mouse_button_up(MOUSEBUTTON btn) { return (this->mouse_states[btn].state == 1); }

	bool get_mouse_button(std::initializer_list<MOUSEBUTTON> btns)
	{
		for (auto btn : btns) if (this->mouse_states[btn].state > 1) return true;
		return false;
	}

	bool get_mouse_button_down(std::initializer_list<MOUSEBUTTON> btns)
	{
		for (auto btn : btns) if (this->mouse_states[btn].state == 2) return true;
		return false;
	}

	bool get_mouse_button_up(std::initializer_list<MOUSEBUTTON> btns)
	{
		for (auto btn : btns) if (this->mouse_states[btn].state == 1) return true;
		return false;
	}

	int get_interpolated_keys(KEYCODE key1, KEYCODE key2) {
		int temp = 0;
		temp += (this->get_key(key2));
		temp -= (this->get_key(key1));
		return temp;
	}

	int get_interpolated_keys(std::initializer_list<KEYCODE> keys1, std::initializer_list<KEYCODE> keys2)
	{
		int temp = 0;
		temp += (this->get_key(keys2));
		temp -= (this->get_key(keys1));
		return temp;
	}

	int get_interpolated_btns(MOUSEBUTTON btn1, MOUSEBUTTON btn2) {
		int temp = 0;
		temp += (this->get_mouse_button(btn2));
		temp -= (this->get_mouse_button(btn1));
		return temp;
	}

	int get_interpolated_keys(std::initializer_list <MOUSEBUTTON> btns1, std::initializer_list <MOUSEBUTTON> btns2)
	{
		int temp = 0;
		temp += (this->get_mouse_button(btns2));
		temp -= (this->get_mouse_button(btns1));
		return temp;
	}

	int get_mouse_x() { return (int)this->mouse_position.x; }
	int get_mouse_y() { return (int)this->mouse_position.y; }
	glm::vec2 get_mouse() { return this->mouse_position; }
};