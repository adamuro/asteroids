#include "game.hpp"

int main () {
	game *g = new game();
	std::cout << g->run() << std::endl;
	delete g;
	return 0;
}

/* TODO:
 * 
 * Main menu
 * Show score
 * Show available bullets
 * Game over screen
 * Highscores
 *
 */