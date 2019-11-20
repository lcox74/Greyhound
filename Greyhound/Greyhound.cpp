
#include <iostream>

#include "src/Asserts.h"
#include "src/GameView.h"

int main()
{
    std::cout << "Hello World!\n";

	auto* win = new GameView("Test Window");

	while (win->window_loop()) { }

	delete(win);

	return EXIT_SUCCESS;
}
