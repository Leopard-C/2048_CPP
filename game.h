#ifndef __GAME_H__
#define __GAME_H__

#include <ncurses.h>

// key-value in ncurses lib 
#define KEY_DOWN  0402  /* down-arrow key  */
#define KEY_UP    0403  /* up-arrow key    */
#define KEY_LEFT  0404  /* left-arrow key  */
#define KEY_RIGHT 0405  /* right-arrow key */
#define KEY_ESC	  033 	/* esc key			   */

typedef enum _Direction { DNull=0, DUp, DDown, DLeft, DRight } Direction;
typedef enum _Status		{ SContinue = 0, SExit, SWin, SLose } Status;
typedef enum _Color {
	COLOR_2 = 1,
	COLOR_4,   COLOR_8,   COLOR_16,  COLOR_32,   COLOR_64,
	COLOR_128, COLOR_256, COLOR_512, COLOR_1024, COLOR_2048 
} COLOR;

class Game {
public:
	Game(int _prob=6, int _scrLeft=4, int _scrTop=4);
	~Game();
public:
	void printGrids();
	void printGridsWithColor();
	int  generateNewNum(Direction direction, int prob);
	bool move();
	void play();
public:	
	void   printInfo(Status s);
	Status judge();

private:
	int  moveLeft();
	int  moveRight();
	int  moveUp();
	int  moveDown();
private:
	int map[4][4];	
	int prob;			// the probablity of generate number 2  range:(0,10]
	int scrLeft;	// the distance from grids's lfet to screen's left 
	int scrTop;		// the distance from grids's top  to screes's top 
};


#endif
