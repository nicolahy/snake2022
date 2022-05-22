### Project 🐍**snake2022**🐍

Resurrection of a student project done in my first year of graduate studies in computer science, totally screwed up at the time.
(Yeah, I like to suffer with the C language).

## Instructions for the project
- The project must be realized in console mode.
- The unit of measurement is the "square": a finite plane of squares constitutes the game board, whose edges can be crossed, and where a snake starts in its middle.
- The snake, which follows the path taken by its head, moves straight ahead at a fixed speed (which increases as it eats the food).
- It will be able to turn according to the good will of the user who will press the corresponding keys of the keyboard.
- As for his "food" that will allow him to grow, it must occupy only one square and there must always be at least one available in the game board.
- When the snake's head is on a square containing food, the food disappears and an additional tail section of one square is added to the snake.
- Once the food is eaten, a new one appears on the game board.
- The allocated memory must be deallocated.

## On which operating system can I play it ?
<img align="left" alt="linux" src="https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black"/>
<br><br/>
And maybe
<br><br/>
<img align="left" alt="windows" src="https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white"/>
<br/><br/>
in the future...

## How to start the game ?
In the root directory of the project, run the make command :
```console
foo@bla:~$ make
```
Go to he ./bin directory and execute :
```console
foo@bla:~$ ./snake
```
After this, read the instructions displayed.

## I want to improve the project, do I need to install a special library ?
Yes, the NCURSES library. Like this :
```
foo@bla:~$ sudo apt-get install libncurses5-dev libncursesw5-dev
```
Don't forget to add the suffix **-lncurses** for the compilation (see the project Makefile).

## Memory leaks
I used Valgrind. You need to install it.
```
foo@bla:~$ sudo apt-get install valgrind
```
In my project, the ncurses library is responsible for the warnings remaining in the leak summary (see below), displayed at the end of the program. Otherwise the memory allocated via malloc is deallocated at the end of the program.
```console
==8134== LEAK SUMMARY:
==8134==    definitely lost: 0 bytes in 0 blocks
==8134==    indirectly lost: 0 bytes in 0 blocks
==8134==    possibly lost: 201 bytes in 3 blocks
==8134==    still reachable: 53,752 bytes in 384 blocks
==8134==    suppressed: 0 bytes in 0 blocks
```

## Here a GIF