CC=gcc
CFLAGS=-Wall -ansi
LDLIBS =-lncurses
OBJ=main.o functions_definitions.o
COLOR_CYAN = /bin/echo -e "\x1b[36m\#\# $1\x1b[0m"


all:
	make snake

snake: $(OBJ)
	$(CC) -o snake $(OBJ) $(CFLAGS) $(LDLIBS)
	mv snake ./bin/
	mv *.o ./obj/
	@echo "[OK] THE EXECUTABLE <SNAKE> HAS BEEN GENERATED IN THE ./BIN/ DIRECTORY"

main.o: ./src/main.c ./src/defines.h ./src/functions_prototypes.h ./src/structs.h
	$(CC) -c ./src/main.c $(CFLAGS)

functions_definitions.o: ./src/functions_definitions.c ./src/functions_prototypes.h
	$(CC) -c ./src/functions_definitions.c $(CFLAGS)

clean:
	rm -f ./bin/* ./data/* ./obj/*.o
	@echo "[OK] THE PROJECT HAS BEEN CLEANED UP !"