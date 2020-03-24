#include "game.hpp"

game::game (): windowWidth(1280.0), windowHeight(960.0) {
	window.create(sf::VideoMode(windowWidth, windowHeight), "Asteroids");
	asteroidTexture.loadFromFile("./images/asteroid1.png");
	clock = sf::Clock();
	bulletsAvailable = 0;
}

void game::run () {
	while(window.isOpen()) { // Main loop
		sf::Event event;
		int time = (int)clock.getElapsedTime().asSeconds();

		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed)
				window.close();
			if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space && bulletsAvailable > 0) {
				bullets.push_back(s.shoot());
				bulletsAvailable--;
			}
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			s.rotate(ship::LEFT);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			s.rotate(ship::RIGHT);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			s.accelerate();

		if(time != lastSecond) {
			lastSecond = time;
			asteroids.push_back(asteroid(window.getPosition(), window.getSize(), asteroidTexture));
			if(bulletsAvailable < 10)
				bulletsAvailable++;
		}

		window.clear();
		drawAsteroids();
		drawBullets();
		drawShip();
		window.display();
	}
}

void game::drawAsteroids () {
	for(asteroid &a: asteroids) {
		a.fly();
		a.draw(&window);
	}
}

void game::drawBullets () {
	for(bullet &b: bullets) {
		b.fly();
		b.draw(&window);
	}
}

void game::drawShip () {
	keepShipOnScreen();
	s.fly();
	s.draw(&window);
}

void game::keepShipOnScreen () {
	if(s.getPosition().x > window.getSize().x - 14.0 ||
	  (s.getPosition().x < 16.0)) {
		s.bounceVer();
	}
	if(s.getPosition().y > window.getSize().y - 14.0 ||
	  (s.getPosition().y < 16.0)) {
		s.bounceHor();
	}
}