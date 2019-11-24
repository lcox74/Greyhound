
#include <iostream>

#include "src/GameView.h"

int main()
{
	GameView* win = new GameView("Test Window", false);

	while (win->window_loop()) { }

	delete(win);

	return EXIT_SUCCESS;
}
