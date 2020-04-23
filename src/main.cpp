#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "menu.hpp"
#include "gameover.hpp"
#include "highscores.hpp"

int main () {
	sf::RenderWindow window(sf::VideoMode(1280.0, 960.0), "Asteroids");
	window.setFramerateLimit(60.0);

	while(window.isOpen()) {
		menu *m = new menu(window);
		game *g;
		gameover *go;
		highscores *h;
		int score;
		int choice = m->run();
		switch(choice) {
			case menu::play:
				g = new game(window);
				score = g->run();
				delete g;
				go = new gameover(window, score);
				go->run();
				delete go;
				break;
			case menu::highscores:
				h = new highscores(window);
				h -> run();
				delete h;
				break;
			case menu::exit:
				window.close();
				break;
		}
		delete m;
	}
	return 0;
}

/* TODO:
 * 
 * Highscores
 *
 */