#ifndef _FUNCTIONS_DEFINITIONS_C
#define _FUNCTIONS_DEFINITIONS_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>
#include "defines.h"
#include "structs.h"
#include "functions_prototypes.h"

/* game board */

/* allocates memory for a character matrix of size lines * columns */
char **allocMatrixChars(unsigned int lines, unsigned int columns) {
	int i;
	char **matrix = malloc(lines*sizeof(char*));

	/*  
	set an matrix (array of arrays) with chars :
	- allocate the main array (which is filled with pointers to the sub-arrays)
	- allocate each of the sub-arrays
	*/ 

	if(matrix == NULL) {
		fprintf(stderr,"[KO] Unable to allocate memory for matrix (1)");
		exit(EXIT_FAILURE);
	}

	for(i = 0 ; i < lines ; ++i) {
		matrix[i] = malloc(columns*sizeof(char));
		if(matrix[i] == NULL) {
			fprintf(stderr,"[KO] Unable to allocate memory for matrix (2)");
			exit(EXIT_FAILURE);
		}
	}
	return matrix;	
}

/* allocates memory for a struct Coordinates table of n elements */
Coordinates *allocTableCoordinates(unsigned int elements) {
	Coordinates *table = malloc(elements*sizeof(Coordinates));

	if(table == NULL) {
		fprintf(stderr,"[KO] Unable to allocate memory for table of struct Coordinates");
		exit(EXIT_FAILURE);
	}
	return table;	
}

/* deletes a position based on coordinates */
void cleanPosition(char **gameBoard, int x, int y) {
	gameBoard[x][y] = EMPTY_SYMBOL;
}

/* Reset the screen */
void clearScreen() {
	clear();
}

/* display the game over screen for the user */
void displayEndScreen(int score) {
	clearScreen();
	printw("                   ___________________________\n");
	printw("                  ||_________________________||\n");
	printw("                  ||                         ||\n");
	printw("                  ||                         ||\n");
	printw("                  ||                         ||\n");
	printw("                  ||         G A M E         ||\n");
	printw("                  ||                         ||\n");
	printw("                  ||         O V E R         ||\n");
	printw("                  ||                         ||\n");
	printw("                  ||                         ||\n");
	printw("                  ||_________________________||\n");
	printw("                  |___________________________|\n");
	printw("                     __|_________________|__||_\n");
	printw("                    |_______________________|| )\n");
	printw("                  ________________________    (__\n");
	printw("                 /oooo  oooo  oooo  oooo /|   _  )_\n");
	printw("                /ooooooooooooooooooooooo/ /  (_)_(_)\n");
	printw("               /ooooooooooooooooooooooo/ /    (o o)\n");
	printw("              /C=_____________________/_/     ==o==\n\n");
	printw("Your obtained score (%d) has been stored in the <score> file which is located in the <data> folder.\n", score);
	printw("Press any key to continue...\n");
}

/* display all the elements of the game board */
void displayGameBoard(char **gameBoard, SnakeComplete *mySnake, Food *food) {

	int i, j;

	/* set complete snake */
	cleanPosition(gameBoard, mySnake->head.previousX, mySnake->head.previousY);
	gameBoard[mySnake->head.x][mySnake->head.y] = SNAKE_SYMBOL_HEAD;

	for(i = 0 ; i < mySnake->currentBodySize ; ++i) {
		cleanPosition(gameBoard, mySnake->body[i].previousX, mySnake->body[i].previousY);
		gameBoard[mySnake->body[i].x][mySnake->body[i].y] = mySnake->body[i].symbol;
	}

	/* set food */
	if(food->isActive) {
    gameBoard[food->coordinates.x][food->coordinates.y] = food->coordinates.symbol;
  }

	for(i = 0; i < LINES; ++i) {
		for(j = 0; j < COLUMNS; ++j) {
			printw("%c",gameBoard[i][j]);
		}
		printw("\n");
	}
}

/* display the rules of the game for the user */
void displayGameRules() {
	printw("===============================================\n");
	printw("==============[KEYBOARD CONTROLS]==============\n");
	printw("===============================================\n");
	printw("| Directional arrows UP - DOWN - LEFT - RIGHT |\n");
	printw("| '%c' or '%c' => Exit game                     |\n", GAME_OVER_KEY_1, GAME_OVER_KEY_2);
	printw("===============================================\n");
	printw("==============[GAME BOARD ELEMENTS]============\n");
	printw("===============================================\n");
	printw("| '%c' => Snake's head                         |\n", SNAKE_SYMBOL_HEAD);
	printw("| '%c' => Snake's body                         |\n", SNAKE_SYMBOL_BODY);
	printw("| '%c' => Food                                 |\n", FOOD_SYMBOL);
	printw("===============================================\n");
	printw("| Press any key to continue...                |\n");
	printw("===============================================\n");
}

/* display the current score to the user */
void displayScore(int score) {
	printw("\nYou have won : %d dollar%c\n", score, score > 1 ? 's' : EMPTY_SYMBOL);
}

/* free the memory allocated for the characters matrix */
void freeMatrixChars(char **matrix, unsigned int lines) {
	if(matrix == NULL) {
		return;
	}

	/* free :
	- first the sub-tables 
	- then the main table 
	*/

	int i;

	for(i = 0; i < lines; ++i) {
		if(matrix[i] != NULL) {
			free(matrix[i]);
		}
	}
	free(matrix);
}

/* free the memory allocated for the struct Coordinates table */
void freeTableCoordinates(Coordinates *table, unsigned int lines) {
	free(table);
}

/* generates random number in range [lower, upper] */
int getRandomInt(int lower, int upper) {
	srand(time(0)); /* Use current time as seed for random generator */
	return (rand() % (upper - lower + 1)) + lower;
}

/* define game speed (in ms) */
void setDelay(unsigned int milliseconds) {
    clock_t pause = milliseconds * (CLOCKS_PER_SEC / 1000);
    clock_t start = clock();
    while((clock() - start) < pause);
}

/* delimits the game board */
void setGameBoardBorders(char **gameBoard) {

	int i,j;

	for(i = 0; i < LINES; ++i) {
		for(j = 0; j < COLUMNS; ++j) {
			gameBoard[i][j] =EMPTY_SYMBOL; /* Toutes les cases de la grille seront vides */
		}
	}

	for(i = 0; i < LINES; ++i) { /* Definit les bords gauche et droit de la grille */
		gameBoard[i][0] = BORDER_SYMBOL_LEFT_RIGHT;
		gameBoard[i][COLUMNS-1] = BORDER_SYMBOL_LEFT_RIGHT;
	}

	for(j = 0; j < COLUMNS; ++j) { /* Definit le haut et le bas de la grille */
		gameBoard[0][j] = BORDER_SYMBOL_UP_DOWN;
		gameBoard[LINES-1][j] = BORDER_SYMBOL_UP_DOWN;
	}
}

/* snake */

/* add element to the snake's body */
void addSnakeBodyItem(SnakeComplete *mySnake) {
		mySnake->currentBodySize += 1;

		if(mySnake->currentBodySize == 1) {
			mySnake->body[0].x = mySnake->head.previousX;
			mySnake->body[0].y = mySnake->head.previousY;
			mySnake->body[0].previousX = mySnake->body[0].x;
			mySnake->body[0].previousY = mySnake->body[0].y;
		} else {
			mySnake->body[mySnake->currentBodySize-1].x = mySnake->body[mySnake->currentBodySize-2].previousX;
			mySnake->body[mySnake->currentBodySize-1].y = mySnake->body[mySnake->currentBodySize-2].previousY;
			mySnake->body[mySnake->currentBodySize-1].previousX = mySnake->body[mySnake->currentBodySize-1].x;
			mySnake->body[mySnake->currentBodySize-1].previousY = mySnake->body[mySnake->currentBodySize-1].y;
		}
}

/* determines the new direction of the snake according to the key pressed */
void moveSnake(char **gameBoard, SnakeComplete *mySnake, bool *isFinished) {
	mySnake->head.previousX = mySnake->head.x;
	mySnake->head.previousY = mySnake->head.y;

  int input = getch();

  switch(input) {		
		case KEY_UP: goTo(gameBoard, mySnake, MOVE_UP); break;
		case KEY_DOWN: goTo(gameBoard, mySnake, MOVE_DOWN); break;
		case KEY_LEFT: goTo(gameBoard, mySnake, MOVE_LEFT); break;
		case KEY_RIGHT: goTo(gameBoard, mySnake, MOVE_RIGHT); break;
		case GAME_OVER_KEY_1: case GAME_OVER_KEY_2: *isFinished = true; break;
		default : goTo(gameBoard, mySnake, mySnake->direction);break;
  }
}

/* recalculates the coordinates of the snake's head according to its direction */
void goTo(char **gameBoard, SnakeComplete *mySnake, int where) {
	switch(where) {
		case MOVE_RIGHT: 
			mySnake->head.previousY = mySnake->head.y;
			mySnake->head.y = mySnake->head.y < COLUMNS - 2 ? mySnake->head.y + MOVE_RIGHT_VALUE : 1;
			break;
		case MOVE_LEFT: 
			mySnake->head.previousY = mySnake->head.y;
			mySnake->head.y = mySnake->head.y > 1 ? mySnake->head.y + MOVE_LEFT_VALUE : COLUMNS - 2;
			break;
		case MOVE_UP: 
			mySnake->head.previousX = mySnake->head.x;
			mySnake->head.x = mySnake->head.x > 1 ? mySnake->head.x + MOVE_UP_VALUE : LINES - 2;
			break;
		case MOVE_DOWN: 
			mySnake->head.previousX = mySnake->head.x;
			mySnake->head.x = mySnake->head.x < LINES - 2 ? mySnake->head.x + MOVE_DOWN_VALUE : 1;
			break;
		default:break;
	}
	mySnake->direction = where;
	gameBoard[mySnake->head.x][mySnake->head.y] = mySnake->head.symbol;
}

/* recalculates the coordinates of the snake's body for each element */
void updateSnakeBody(SnakeComplete *mySnake) {

	int i;

	for(i = 0 ; i < mySnake->currentBodySize ; ++i) {
		if(i == 0) { /* there is only the snake's head on the gameboard */
			mySnake->body[0].previousX = mySnake->body[0].x;
			mySnake->body[0].previousY = mySnake->body[0].y;
			mySnake->body[0].x = mySnake->head.previousX;
			mySnake->body[0].y = mySnake->head.previousY;
			mySnake->body[0].symbol = SNAKE_SYMBOL_BODY;
		} else {
			mySnake->body[i].previousX = mySnake->body[i].x;
			mySnake->body[i].previousY = mySnake->body[i].y;
			mySnake->body[i].x = mySnake->body[i-1].previousX;
			mySnake->body[i].y = mySnake->body[i-1].previousY;
			mySnake->body[i].symbol = SNAKE_SYMBOL_BODY;
		}
	}
}

/* food */

/* detect when the food was eaten */
bool isFoodEaten(char **gameBoard, Food *food) {
	return gameBoard[food->coordinates.x][food->coordinates.y] != food->coordinates.symbol;
}
/* set food coordinates */
void setFood(char **gameBoard, Food *food) {
	food->coordinates.x = getRandomInt(1, LINES-1);
	food->coordinates.y = getRandomInt(1, COLUMNS-1);
	food->isActive = gameBoard[food->coordinates.x][food->coordinates.y] == EMPTY_SYMBOL;
}

/* speed */

/* display the current game speed to the user */
void displaySpeed(unsigned int speed) {
	printw("\nYour speed : %0.01f cases/seconde\n", 1000.00 * 1 / speed); /* cross product to get nbCases/second */
}

/* improves game speed by reducing pause times */
void updateSpeed(int *speed) {
	int newSpeed;
	newSpeed = *speed -= SPEED_DECREMENT;
	if(newSpeed <= 100) {
		*speed = 100;
	}
}

/* file */

void saveScore(int score) {

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

  FILE* file = fopen("./data/score.txt","a");

  if(file != NULL) {
  	fprintf(file ,"[%d-%02d-%02d %02d:%02d:%02d] Score : %d\n", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, score);
  }
  fclose(file);
}

#endif