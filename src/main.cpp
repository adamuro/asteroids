#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "menu.hpp"
#include "gameover.hpp"

int main () {
	sf::RenderWindow window(sf::VideoMode(1280.0, 960.0), "Asteroids");
	window.setFramerateLimit(60.0);

	while(window.isOpen()) {
		menu *m = new menu(window);
		game *g = new game(window);
		int score;
		gameover *go;
		int choice = m->run();
		switch(choice) {
			case menu::play:
				score = g->run();
				go = new gameover(window, score);
				go->run();
				break;
			case menu::exit:
				window.close();
				break;
		}
		delete m;
		delete g;
	}
	return 0;
}

/* TODO:
 * 
 * Game over screen
 * Highscores
 *
 */