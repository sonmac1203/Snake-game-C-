#pragma once
#include <iostream> 
#include <conio.h> // a new library
#include <ctime>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

const int width = 21; // width of the board
const int height = 21; // height of the board
int x, y, prey_x, prey_y; // coordinates
bool game_over;
enum direction { stop = 0, up, left, down, right };
direction dir;
int score = 0;
int tail_x[100], tail_y[100];
int num_tail = 0;

void game_setup() {
	game_over = false;

	// center of the board
	x = (width - 1) / 2;
	y = (height - 1) / 2;
	srand((unsigned)time(0));
	do {
		prey_x = (rand() % (width - 1)) + 1;
		prey_y = (rand() % (height - 1)) + 1;
	} while (prey_x == 0 || prey_x == width || prey_y == 0 || prey_y == height || (prey_x == x && prey_y == y));

}

void game_draw() {
	system("cls"); // clear the screen

	// Draw the board
	for (int i = 0; i < height; i++) {
		if (i == 0 || i == height - 1) {
			for (int j = 0; j < width; j++) {
				std::cout << "#";
			}
		}
		else {
			for (int j = 0; j < width; j++) {
				if (j == 0 || j == width - 1) {
					std::cout << "#";
				}
				else {
					if (i == y && j == x) { // Print the location of snake
						std::cout << "O";
					}
					else if (i == prey_y && j == prey_x) { // Print the location of the prey
						std::cout << "X";
					}
					else {
						bool not_print = true;
						for (int k = 0; k < num_tail; k++) {
							if (i == tail_y[k] && j == tail_x[k]) {
								std::cout << "o";
								not_print = false;
							}
						}
						if (not_print)
							std::cout << " ";
					}
				}
			}
		}
		std::cout << std::endl;
	}
	std::cout << "Score: " << score << std::endl;
}

void game_input() {

	int c = 0;

	if (_kbhit()) { // returns true if a character on the keyboard is pressed
		switch (c = _getch()) {
		case KEY_UP:
			dir = up;
			break;
		case KEY_LEFT:
			dir = left;
			break;
		case KEY_DOWN:
			dir = down;
			break;
		case KEY_RIGHT:
			dir = right;
			break;
		case 'x':
			game_over = true;
			break;
		default:
			break;
		}
	}
}

void game_logic() {
	int prev_x, prev_y, prev_xx, prev_yy;

	// Logic of the tail
	if (num_tail > 0) {
		prev_x = tail_x[0];
		prev_y = tail_y[0];
		tail_x[0] = x;
		tail_y[0] = y;
		for (int i = 1; i < num_tail; i++) {
			prev_xx = tail_x[i];
			prev_yy = tail_y[i];
			tail_x[i] = prev_x;
			tail_y[i] = prev_y;
			prev_x = prev_xx;
			prev_y = prev_yy;
		}
	}


	switch (dir) { // directions control
	case up:
		y--;
		break;
	case left:
		x--;
		break;
	case down:
		y++;
		break;
	case right:
		x++;
		break;
	default:
		break;
	}

	// meet the prey
	if (x == prey_x && y == prey_y) {
		score += 10;
		do {
			prey_x = (rand() % (width - 1)) + 1;
			prey_y = (rand() % (height - 1)) + 1;
		} while (prey_x == 0 || prey_x == width || prey_y == 0 || prey_y == height);
		num_tail++;
	}


	if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
		game_over = true;
	}

	for (int k = 0; k < num_tail; k++) {
		if (x == tail_x[k] && y == tail_y[k]) {
			game_over = true;
		}
	}


}
