
#include <iostream>

#include "src/GameView.h"

int main()
{
	auto* win = new GameView("Test Window");

	while (win->window_loop()) { }

	delete(win);

	return EXIT_SUCCESS;
}
