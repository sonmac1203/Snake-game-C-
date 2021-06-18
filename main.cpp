// Making a simple snake game

#include <iostream>
#include <Windows.h>
#include "methods.h"

int main() {
	game_setup();
	while (!game_over) {
		game_draw();
		game_input();
		game_logic();
		Sleep(10); // Slow down
	}
	std::cout << "Game Over!" << std::endl;;

	return 0;
}

