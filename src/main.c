#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>

#include "defines.h"
#include "structs.h"
#include "functions_prototypes.h"

/* Let's gooooo */
int main(int argc,char *argv[]) {

	initscr(); /* Start curses mode */
	raw(); /* Line buffering disabled	*/
	keypad(stdscr, TRUE);	/* We get F1, F2 etc.. */
	cbreak();
	noecho(); /* Don't echo() while we do getch */
	nodelay(stdscr, TRUE);

	clearScreen();
	displayGameRules();

	refresh(); /* Print it on to the real screen */
	getchar();

	char **gameBoard = allocMatrixChars(LINES,COLUMNS);
	int score = 0, speed = SPEED_START;
	bool isFinished = false;

	/* initialize snake */
	SnakeComplete mySnake;
	mySnake.direction = MOVE_RIGHT;
	mySnake.currentBodySize = 0;
	mySnake.head.x = SNAKE_START_X;
	mySnake.head.y = SNAKE_START_Y;
	mySnake.head.previousX = SNAKE_START_X;
	mySnake.head.previousY = SNAKE_START_Y;
	mySnake.head.symbol = SNAKE_SYMBOL_HEAD;

	/* initialize food */
	Food food;
	food.coordinates.symbol = FOOD_SYMBOL;

	setGameBoardBorders(gameBoard);
	setFood(gameBoard, &food);

	displayGameBoard(gameBoard, &mySnake, &food);
	displayScore(score);
	displaySpeed(speed);

	refresh(); /* Print it on to the real screen */

	while(!isFinished && mySnake.currentBodySize < SNAKE_MAXLENGTH_BODY) {
		clearScreen();
		moveSnake(gameBoard, &mySnake, &isFinished);
		if(isFinished) {
			break;
		}
		if(isFoodEaten(gameBoard, &food)) {
			++score;
			addSnakeBodyItem(&mySnake);
			setFood(gameBoard, &food);
			updateSpeed(&speed);
		}
		updateSnakeBody(&mySnake);
		displayGameBoard(gameBoard, &mySnake, &food);
		displayScore(score);
		displaySpeed(speed);
		refresh(); /* Print it on to the real screen */
		setDelay(speed);
	}

	saveScore(score); 
	clearScreen(); 
	displayEndScreen(score); 
	refresh();
	getchar();

	endwin();	/* End curses mode */

  return 0;
}