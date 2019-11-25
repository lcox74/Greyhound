#include "GH_Window.h"


void GH_Window::init(std::string name, int width, int height, bool bfullscreen)
{
	this->name = name;
	this->width = width;
	this->height = height;
	this->bfullscreen = bfullscreen;

	// Initialise SDL
	FATAL_ASSERT_MESS((SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) == 0), SDL_GetError());

	//Use OpenGL 3.1 core
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	// Anti aliasing
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 2);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);
	glEnable(GL_MULTISAMPLE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Create SDL GH_Window
	this->sdl_window = SDL_CreateWindow(this->name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN | ((this->bfullscreen) ? SDL_WINDOW_FULLSCREEN : 0));
	FATAL_ASSERT_MESS((this->sdl_window != NULL), SDL_GetError());

	// Create GL Context
	this->gl_context = SDL_GL_CreateContext(this->sdl_window);
	FATAL_ASSERT_MESS((this->gl_context != NULL), SDL_GetError());

	// Initalise GLEW
	glewExperimental = GL_TRUE;
	FATAL_ASSERT_MESS((glewInit() == GLEW_OK), SDL_GetError());
	FATAL_ASSERT_MESS((SDL_GL_SetSwapInterval(1) >= 0), SDL_GetError());

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	this->graphics = new GH_Graphics(this->width, this->height);
	this->input = new GH_Input();
	this->ui = new GH_UI(this->graphics, this->input);

	// Define the viewport dimensions
	glViewport(0, 0, this->width, this->height);

	// Set OpenGL options
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Configure VAO/VBO for texture quads
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Fill frame list to fix initial smoothing
	this->frame_list = std::vector<double>(this->frame_smooth);
	std::fill(this->frame_list.begin(), this->frame_list.end(), 1 / this->frame_rate_max);
}

int GH_Window::window_loop()
{
	this->frame_last = this->frame_now;
	this->frame_now = SDL_GetTicks();

	input->input_update();

	// Get SDL Event and handle quit event
	while (SDL_PollEvent(&this->sdl_event)) 
	{
		switch (this->sdl_event.type)
		{
		case SDL_KEYDOWN:
			input->update_key((KEYCODE)this->sdl_event.key.keysym.sym, 2);
			break;
		case SDL_KEYUP:
			input->update_key((KEYCODE)this->sdl_event.key.keysym.sym, 1);
			break;
		case SDL_MOUSEBUTTONDOWN:
			input->update_button((MOUSEBUTTON)this->sdl_event.button.button, 2);
			break;
		case SDL_MOUSEBUTTONUP:
			input->update_button((MOUSEBUTTON)this->sdl_event.button.button, 1);
			break;
		case SDL_MOUSEMOTION:
			input->update_mouse_position(this->sdl_event.motion.x, this->sdl_event.motion.y);
			break;
		case SDL_QUIT:
			return 0;
		}
	}

	// Clear GH_Window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Render GH_Window
	this->Update();

	// Display UI
	this->ui->update();

	// Swap buffers to display to GH_Window
	if (!this->pause_window) {
		glFlush();
		SDL_GL_SwapWindow(this->sdl_window);
	}
	

	this->delta_time = (double)(1.0 / (this->frame_now - this->frame_last));
	this->frame_list.push_back(this->delta_time);

	if (this->frame_list.size() >= (unsigned)this->frame_smooth) 
	{
		this->frame_list.erase(this->frame_list.begin());
		this->frame_list.pop_back();
	}

	return 1;
}


void GH_Window::set_window_borderless() { SDL_SetWindowBordered(this->sdl_window, SDL_FALSE); }

void GH_Window::set_window_bordered() { SDL_SetWindowBordered(this->sdl_window, SDL_TRUE);  }

float GH_Window::get_delta_time()
{
	return (float)this->delta_time;
}

float GH_Window::get_delta_time_smooth()
{
	return (float)std::accumulate(this->frame_list.begin(), this->frame_list.end(), 0.0) / this->frame_list.size();
}

int GH_Window::get_frame_rate()
{
	return (int) (1000.0 / (1.0 / this->delta_time));
}

int GH_Window::get_frame_rate_smooth()
{
	float average = (float)std::accumulate(this->frame_list.begin(), this->frame_list.end(), 0.0) / this->frame_list.size();
	return (int)( 1000.0 / (1.0 /  average));
}

int GH_Window::get_max_frame_rate() { return this->frame_rate_max; }
void GH_Window::set_max_frame_rate(int max) { this->frame_rate_max = max; }

void GH_Window::clean()
{
	SDL_GL_DeleteContext(this->gl_context);
	SDL_DestroyWindow(this->sdl_window);
	SDL_Quit();
}