CC = g++
CFLAGS = -Wall -Werror -pedantic
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

OBJ =\
	./src/main.cpp \
	./src/game.cpp \
	./src/ship.cpp \
	./src/bullet.cpp \
	./src/asteroid.cpp \
	./src/menu.cpp \
	./src/gameover.cpp \
	./src/highscores.cpp

all: main

clean:
		rm -f *.o asteroids

.cpp.o:
		$(CC) -c $(INCLUDES) $(CFLAGS) $<

main: $(OBJ)
		$(CC) $(OBJ) $(LIBS) $(CFLAGS) -o asteroids