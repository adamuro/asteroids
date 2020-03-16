#include "game.hpp"

game::game () {
	window.create(sf::VideoMode(1280.0, 960.0), "Asteroids");

	s = new ship(window.getSize().x / 2, window.getSize().y / 2);
	a = new asteroid(window.getPosition(), window.getSize());
}

void game::run () {
	while(window.isOpen()) { // Main loop
		sf::Event windowEvent;

		while(window.pollEvent(windowEvent)) {
			if(windowEvent.type == sf::Event::Closed)
				window.close();	
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			s->rotate(ship::LEFT);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			s->rotate(ship::RIGHT);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			s->accelerate();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			s->breaks();

		s->fly();
		a->fly();
		window.clear();
		a->draw(&window);
		s->draw(&window);
		window.display();
	}
}