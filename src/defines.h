#ifndef _DEFINES_H
#define _DEFINES_H

/* game board */
#define LINES 20
#define COLUMNS 50
#define BORDER_SYMBOL_LEFT_RIGHT '|'
#define BORDER_SYMBOL_UP_DOWN '='

/* symbols */
#define SNAKE_SYMBOL_HEAD '@'
#define SNAKE_SYMBOL_BODY 'o'
#define SNAKE_MAXLENGTH_BODY 100
#define FOOD_SYMBOL '$'
#define EMPTY_SYMBOL ' '

/* snake */
#define SNAKE_START_X LINES/2
#define SNAKE_START_Y COLUMNS/2
#define MOVE_UP 1
#define MOVE_DOWN 2
#define MOVE_LEFT 3
#define MOVE_RIGHT 4
#define MOVE_UP_VALUE -1
#define MOVE_DOWN_VALUE 1
#define MOVE_LEFT_VALUE -1
#define MOVE_RIGHT_VALUE 1

/* speed */
#define SPEED_START 150
#define SPEED_DECREMENT 1

/* other */
#define GAME_OVER_KEY_1 'q'
#define GAME_OVER_KEY_2 'Q'

#endif