CC = g++
CFLAGS = -Wall -Werror -pedantic
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

OBJ =\
	./src/main.cpp \
	./src/game.cpp \
	./src/ship.cpp \
	./src/asteroid.cpp

all: main

clean:
		rm -f *.o chess

.cpp.o:
		$(CC) -c $(INCLUDES) $(CFLAGS) $<

main: $(OBJ)
		$(CC) $(OBJ) $(LIBS) $(CFLAGS) -o asteroids