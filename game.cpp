
#include "game.h"

#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cstring>

Game::Game(int _prob/*=6*/, int _scrLeft/*=4*/, int _scrTop/*=4*/) 
	: prob(_prob) , scrLeft(_scrLeft), scrTop(_scrTop) 
{
	memset(map, 0, sizeof(map));
	// initialize ncurses lib
	initscr();
	keypad(stdscr, true);
	start_color();

	init_pair(COLOR_2,    COLOR_WHITE,   COLOR_BLACK);
	init_pair(COLOR_4,    COLOR_YELLOW,  COLOR_BLACK);
	init_pair(COLOR_8,    COLOR_GREEN,   COLOR_BLACK);
	init_pair(COLOR_16,   COLOR_CYAN,    COLOR_BLACK);
	init_pair(COLOR_32,   COLOR_BLUE,    COLOR_BLACK);
	init_pair(COLOR_64,   COLOR_MAGENTA, COLOR_BLACK);
	init_pair(COLOR_128,  COLOR_RED,     COLOR_BLACK);
	init_pair(COLOR_256,  COLOR_WHITE,   COLOR_GREEN);
	init_pair(COLOR_512,  COLOR_WHITE,   COLOR_YELLOW);
	init_pair(COLOR_1024, COLOR_WHITE,   COLOR_MAGENTA);
	init_pair(COLOR_2048, COLOR_WHITE,   COLOR_RED);	
}

Game::~Game() {
	endwin();
}


// print grids (refresh)
void Game::printGrids()
{
	int i = scrTop, j = scrLeft;

	// print the line with num
	// if the map[row][col] is zero, doesn't print it 
	auto printNum = [this](int scrRow, int scrCol, int mapRow){
		char _map[5][4];
		// convert the num to string 
		// if num is zero, num_str = "",  in this way, the num wont't be printed 
		// else num_str = ("%d", num)
		for (int mapCol = 0; mapCol < 4; ++mapCol) {
			memset(_map[mapCol], 0, sizeof(_map[mapCol]));
			if (map[mapRow][mapCol] == 0) {
				strcpy(_map[mapCol], ""); 
			}
			else {
				snprintf(_map[mapCol], 4, "%d", map[mapRow][mapCol]);
			}
		}
		mvprintw(scrRow, scrCol, "|  %4s  |  %4s  |  %4s  |  %4s  |", _map[0], _map[1], _map[2], _map[3]);
	};

	mvprintw(i++, j, "+ ------ + ------ + ------ + ------ +");
	mvprintw(i++, j, "|        |        |        |        |");
	printNum(i++, j, 0);																				// call lambda function: printNum 
	mvprintw(i++, j, "|        |        |        |        |");
	mvprintw(i++, j, "+ ------ + ------ + ------ + ------ +");
	mvprintw(i++, j, "|        |        |        |        |");
	printNum(i++, j, 1);
	mvprintw(i++, j, "|        |        |        |        |");
	mvprintw(i++, j, "+ ------ + ------ + ------ + ------ +");
	mvprintw(i++, j, "|        |        |        |        |");
	printNum(i++, j, 2);
	mvprintw(i++, j, "|        |        |        |        |");
	mvprintw(i++, j, "+ ------ + ------ + ------ + ------ +");
	mvprintw(i++, j, "|        |        |        |        |");
	printNum(i++, j, 3);
	mvprintw(i++, j, "|        |        |        |        |");
	mvprintw(i++, j, "+ ------ + ------ + ------ + ------ +");
}

void Game::printGridsWithColor() {
	int i = scrTop, j = scrLeft;
		
	// print the line with num
	// if the map[row][col] is zero, doesn't print it 
	auto printNum = [&](int scrRow, int scrCol, int mapRow){
		auto loadColor = [&](int mapRow, int mapCol, COLOR c){
			attron(COLOR_PAIR(c));
			mvprintw(scrRow, scrCol + 1 + mapCol * 9, "  ");
			mvprintw(scrRow, scrCol + 3 + mapCol * 9, "%4d", map[mapRow][mapCol]);
			mvprintw(scrRow, scrCol + 7 + mapCol * 9, "  |");
			attroff(COLOR_PAIR(c));
		};
		
		mvprintw(scrRow, scrCol, "|");
		for (int mapCol = 0; mapCol < 4; ++mapCol) {
			switch(map[mapRow][mapCol]) {
			default:
				break;
			case 0:
				break;
			case 2:
				loadColor(mapRow, mapCol, COLOR_2);
				break;
			case 4:
				loadColor(mapRow, mapCol, COLOR_4);
				break;
			case 8:
				loadColor(mapRow, mapCol, COLOR_8);
				break;
			case 16:
				loadColor(mapRow, mapCol, COLOR_16);
				break;
			case 32:
				loadColor(mapRow, mapCol, COLOR_32);
				break;
			case 64:
				loadColor(mapRow, mapCol, COLOR_64);
				break;
			case 128:
				loadColor(mapRow, mapCol, COLOR_128);
				break;
			case 256:
				loadColor(mapRow, mapCol, COLOR_256);
				break;
			case 512:
				loadColor(mapRow, mapCol, COLOR_512);
				break;
			case 1024:
				loadColor(mapRow, mapCol, COLOR_1024);
				break;
			case 2048:
				loadColor(mapRow, mapCol, COLOR_2048);
				break;
			}
		}
	};

	mvprintw(i++, j, "+ ------ + ------ + ------ + ------ +");
	mvprintw(i++, j, "|        |        |        |        |");
	printNum(i++, j, 0);																				// call lambda function: printNum 
	mvprintw(i++, j, "|        |        |        |        |");
	mvprintw(i++, j, "+ ------ + ------ + ------ + ------ +");
	mvprintw(i++, j, "|        |        |        |        |");
	printNum(i++, j, 1);
	mvprintw(i++, j, "|        |        |        |        |");
	mvprintw(i++, j, "+ ------ + ------ + ------ + ------ +");
	mvprintw(i++, j, "|        |        |        |        |");
	printNum(i++, j, 2);
	mvprintw(i++, j, "|        |        |        |        |");
	mvprintw(i++, j, "+ ------ + ------ + ------ + ------ +");
	mvprintw(i++, j, "|        |        |        |        |");
	printNum(i++, j, 3);
	mvprintw(i++, j, "|        |        |        |        |");
	mvprintw(i++, j, "+ ------ + ------ + ------ + ------ +");

}

// generate the number 2 or 4
// prob: the probablity of generate 2		range:(0, 10]
int Game::generateNewNum(Direction direction, int prob) {
	srand((unsigned int)time(NULL));

	int num = 0;
	int row = rand() % 4;
	int col = rand() % 4;

	if (prob <= 0)
		prob = 1;
	if (prob > 10)
		prob = 10;

	int base[10] = { 0 };
	for (int i = 0; i < prob; ++i)
		base[i] = 2;
	for (int i = prob; i < 10; ++i)
		base[i] = 4;
	
	num = base[num % 10];

	// judge the arrow-direction the use press 
	switch (direction) {
		default:
			break;
		case DUp:
			if (map[3][col] == 0) {
				map[3][col] = num;
			}
			else {
				for (col = 0; col < 4; ++col) {
					if (map[3][col] == 0) {
						map[3][col]= num;
						break;
					}
				}
			}
			break;
		case DDown:
			if (map[0][col] == 0) {
				map[0][col] = num;
			}
			else {
				for (col = 0; col < 4; ++col) {
					if (map[0][col] == 0) {
						map[0][col] = num;
						break;
					}
				}
			}
			break;
		case DLeft:
			if (map[row][3] == 0) {
				map[row][3] = num;
			}
			else {
				for (row = 0; row < 4; ++row) {
					if (map[row][3] == 0) {
						map[row][3] = num;
						break;
					}
				}
			}
			break;
		case DRight:
			if (map[row][0] == 0) {
				map[row][0] = num;
			}
			else {
				for (row = 0; row < 4; ++row) {
					if (map[row][0] == 0) {
						map[row][0] = num;
						break;
					}
				}
			}
			break;
		case DNull:
			map[row][col] = num;
			break;
	}

	return num;
}


// paly game, press 'Up, Down, Left, Right-arrow' key
bool Game::move() {
	int key;
	key = getch();
	
	switch(key) {
		case KEY_UP:		// UP
			//direction = moveUp();
			moveUp();
			break;
		case KEY_DOWN:		// Down
			//direction = moveDown();
			moveDown();
			break;
		case KEY_LEFT:		// Left
			//direction = moveLeft();
			moveLeft();
			break;
		case KEY_RIGHT:		// Right
			//direction = moveRight();
			moveRight();
			break;
		case KEY_ESC:
			return false;
			break;
	}
	
	refresh();
	return true;
}

int Game::moveDown() {
	int row, col, tmp;
	for (col = 0; col < 4; ++col) {
		int n = 4;
		while (n--) {
			for (row = 3; row > 0; --row) {
				if (map[row][col] == 0) {
					for (tmp = row; tmp > 0; --tmp) {
						map[tmp][col] = map[tmp-1][col];
						map[tmp-1][col] = 0;
					}
				}
			}
		}
		for (row = 3; row > 0; --row) {
			if (map[row][col] == map[row-1][col]) {
				map[row][col] *= 2;
				for (tmp = row - 1; tmp > 0; --tmp) {
					map[tmp][col] = map[tmp-1][col];
					map[tmp-1][col] = 0;
				}
			}
		}
	}
	generateNewNum(DDown, prob);
}

// press right-arrow key
int Game::moveRight() {
	int row, col, tmp;
	for (row = 0; row < 4; ++row) {
		int n = 4;
		while (n--) {
			for (col = 3; col > 0; --col) {
				if (map[row][col] == 0) {
					for (tmp = col; tmp > 0; --tmp) {
						map[row][tmp] = map[row][tmp-1];
						map[row][tmp-1] = 0;
					}
				}
			}
		}

		for (col = 3; col > 0; --col) {
			if (map[row][col] == map[row][col-1]) {
				map[row][col] *= 2;
				for (tmp = col - 1; tmp > 0; --tmp) {
					map[row][tmp] = map[row][tmp-1];
					map[row][tmp-1] = 0;
				}
			}
		}
	}
	
	generateNewNum(DRight, prob);
}

int Game::moveLeft() {
	int row, col, tmp;
	for (row = 0; row < 4; ++row) {
		int n = 4;
		
		while (n--) {
			for (col = 0; col < 3; ++col) {
				if (map[row][col] == 0) {
					for (tmp = col; tmp < 3; ++tmp) {
						map[row][tmp] = map[row][tmp+1];
						map[row][tmp+1] = 0;
					}
				}
			}
		}

		for (col = 0; col < 3; ++col) {
			if (map[row][col] == map[row][col+1]) {
				map[row][col] *= 2;
				for (tmp = col + 1; tmp < 3; ++tmp) {
					map[row][tmp] = map[row][tmp+1];
					map[row][tmp+1] = 0;
				}
			}
		}
	}

	generateNewNum(DLeft, prob);
}

// press up-arrow key 
int Game::moveUp() {
	int row, col, tmp;
	for (col = 0; col < 4; ++col) {
		int n = 4;
		while(n--) {
			for (row = 0; row < 3; ++row) {
				if (map[row][col] == 0) {
					for (tmp = row; tmp < 3; ++tmp) {
						map[tmp][col] = map[tmp+1][col];
						map[tmp+1][col] = 0;
					}
				}
			}
		}

		for (row = 0; row < 3; ++row) {
			if (map[row][col] == map[row+1][col]) {
				map[row][col] *= 2;
				//map[row+1][col] = 0;
				for (tmp = row + 1; tmp < 3; ++tmp) {
					map[tmp][col] = map[tmp+1][col];
					map[tmp+1][col] = 0;
				}
			}
		}
	}
	generateNewNum(DUp, prob);
}

void Game::printInfo(Status s) {
	switch (s) {
	case SWin:
		mvprintw(scrTop + 18, 1, "Congratulations!!!");	
		break;
	case SLose:
		mvprintw(scrTop + 18, 1, "Game Over!");	
		break;
	case SExit:
		break;
	}
}

// judge if the player has won
Status Game::judge() {
	// win 
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (map[i][i] == 2048) {
				return SWin;
			}
		}
	}
	
	// continue
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (map[i][j] == map[i][j+1]){
				return SContinue;
			}
		}
	}
	for (int j = 0; j < 4; ++j) {
		for (int i = 0; i < 3; ++i) {
			if (map[i][j] == map[i+1][j]){
				return SContinue;
			}
		}
	}

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (map[i][j] == 0) {
				return SContinue;
			}
		}
	}

	// lose
	return SLose;
}

void Game::play() {
	generateNewNum(DNull, prob);
	clear();						// function to clear the screen ( provided by ncurses lib)
	printGridsWithColor();
	
	while (true) {		
		if (!move()) {
			printInfo(SExit);
			break;
		}
		clear();
		printGridsWithColor();
		
		// 判断游戏是否继续
		if (judge() == SWin) {
			printInfo(SWin);
			break;
		}
		else if (judge() == SLose) {
			printInfo(SLose);
			break;
		}
		else{
			continue;
		}
	}

	getch();
}

