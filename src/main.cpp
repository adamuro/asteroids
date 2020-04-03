#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.hpp"

int main () {
	sf::RenderWindow window(sf::VideoMode(1280.0, 960.0), "Asteroids");
	window.setFramerateLimit(60.0);

	while(window.isOpen()) {
		game *g = new game(window);
		g->run();
		delete g;
	}
	return 0;
}

/* TODO:
 * 
 * Main menu
 * Game over screen
 * Highscores
 *
 */