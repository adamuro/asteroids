#include "game.hpp"

int main () {
	game *g = new game();
	g->run();
	delete g;
	return 0;
}