#ifndef _FUNCTIONS_PROTOTYPES_H
#define _FUNCTIONS_PROTOTYPES_H

/* game board */
char **allocMatrixChars(unsigned int, unsigned int);
void cleanPosition(char [LINES][COLUMNS], int, int);
void clearScreen();
void displayEndScreen(int score);
void displayGameBoard(char [LINES][COLUMNS], SnakeComplete*, Food*);
void displayGameRules();
void displayScore(int);
void freeMatrixChars(char**, unsigned int);
int getRandomInt(int, int);
void setDelay(unsigned int);
void setGameBoardBorders(char [LINES][COLUMNS]);

/* snake */
void addSnakeBodyItem(SnakeComplete*);
void moveSnake(char [LINES][COLUMNS], SnakeComplete*, bool*);
void goTo(char [LINES][COLUMNS], SnakeComplete*, int);
void updateSnakeBody(SnakeComplete*);

/* food */
bool isFoodEaten(char [LINES][COLUMNS], Food*);
void setFood(char [LINES][COLUMNS], Food*);

/* speed */
void displaySpeed(unsigned int);
void updateSpeed(int*);

/* file */
void saveScore(int score);

#endif