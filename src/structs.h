#ifndef _STRUCTS_H
#define _STRUCTS_H

typedef struct coordinates {
	char symbol;
	int x;
	int y;
	int previousX;
	int previousY;
} Coordinates;

typedef struct snakeComplete {
	int direction;
	int currentBodySize;
	Coordinates head;
	Coordinates body[SNAKE_MAXLENGTH_BODY];
} SnakeComplete;

typedef struct food {
	bool isActive;
	Coordinates coordinates;
} Food;

#endif