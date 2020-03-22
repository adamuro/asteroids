#include "game.hpp"

int main () {
	game *g = new game();
	g->run();
	delete g;
	return 0;
}

/* TODO:
 * 
 * Main menu
 * Collisions
 * Show score
 * Show available bullets
 * Game over screen
 * Highscores
 *
 */