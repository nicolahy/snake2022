#ifndef _FUNCTIONS_PROTOTYPES_H
#define _FUNCTIONS_PROTOTYPES_H

/* game board */
char**allocMatrixChars(unsigned int, unsigned int);
void cleanPosition(char**, int, int);
void clearScreen();
void displayEndScreen(int score);
void displayGameBoard(char**, SnakeComplete*, Food*);
void displayGameRules();
void displayScore(int);
void freeMatrixChars(char**, unsigned int);
int getRandomInt(int, int);
void setDelay(unsigned int);
void setGameBoardBorders(char**);

/* snake */
void addSnakeBodyItem(SnakeComplete*);
void moveSnake(char**, SnakeComplete*, bool*);
void goTo(char**, SnakeComplete*, int);
void updateSnakeBody(SnakeComplete*);

/* food */
bool isFoodEaten(char**, Food*);
void setFood(char**, Food*);

/* speed */
void displaySpeed(unsigned int);
void updateSpeed(int*);

/* file */
void saveScore(int score);

#endif