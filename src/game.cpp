#include "game.hpp"

game::game () {
	window.create(sf::VideoMode(1280.0, 960.0), "Asteroids");
	asteroidTexture.loadFromFile("./images/asteroid1.png");
	clock = sf::Clock();
}

void game::run () {
	while(window.isOpen()) { // Main loop
		sf::Event windowEvent;

		while(window.pollEvent(windowEvent)) {
			if(windowEvent.type == sf::Event::Closed)
				window.close();	
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			s.rotate(ship::LEFT);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			s.rotate(ship::RIGHT);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			s.accelerate();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			s.breaks();

		int time = (int)clock.getElapsedTime().asSeconds();
		if(time != lastAsteroidTime) {
			asteroids.push_back(asteroid(window.getPosition(), window.getSize(), asteroidTexture));
			lastAsteroidTime = time;
		}

		window.clear();
		drawAsteroids();
		s.fly();
		s.draw(&window);
		window.display();
	}
}

void game::drawAsteroids () {
	for(asteroid &a: asteroids) {
		a.fly();
		a.draw(&window);
	}
}