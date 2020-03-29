#include "game.hpp"

game::game (): windowWidth(1280.0), windowHeight(960.0) {
	window.create(sf::VideoMode(windowWidth, windowHeight), "Asteroids");
	window.setFramerateLimit(60.0);
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
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			s.accelerate();
		}
		s.fly();

		if(time > 0) {
			clock.restart();
			asteroids.push_back(new asteroid(window.getSize(), asteroidTexture));
			if(bulletsAvailable < 10)
				bulletsAvailable++;
		}
		for(uint i = 0; i < asteroids.size(); i++) {
			for(uint j = 0; j < bullets.size(); j++) {
				if(bullets[j]->offScreen(&window)) {
					delete bullets[j];
					bullets.erase(bullets.begin() + j);
				}
				else if(collision(bullets[j]->getSprite(), asteroids[i]->getSprite(), bullets[j]->getSprite().getTexture()->copyToImage(), asteroids[i]->getSprite().getTexture()->copyToImage())) {
					delete bullets[j];
					delete asteroids[i];
					bullets.erase(bullets.begin() + j);
					asteroids.erase(asteroids.begin() + i);
				}
			}
			if(i < asteroids.size() && asteroids[i]->offScreen(&window)) {
				delete asteroids[i];
				asteroids.erase(asteroids.begin() + i);
			}
			if(collision(s.getSprite(), asteroids[i]->getSprite(), s.getSprite().getTexture()->copyToImage(), asteroids[i]->getSprite().getTexture()->copyToImage())) {
				return;
			}
		}

		window.clear();
		drawAsteroids();
		drawBullets();
		drawShip();
		window.display();
	}
}

void game::drawAsteroids () {
	for(asteroid *a: asteroids) {
		a->fly();
		a->draw(&window);
	}
}

void game::drawBullets () {
	for(bullet *b: bullets) {
		b->fly();
		b->draw(&window);
	}
}

void game::drawShip () {
	keepShipOnScreen();
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

sf::IntRect game::FToIRect(const sf::FloatRect& f) {
	return sf::IntRect((int) f.left, (int) f.top, (int) f.width, (int) f.height);
}

bool game::collision(const sf::Sprite &a, const sf::Sprite &b, const sf::Image &imgA, const sf::Image &imgB) {
	sf::IntRect boundsA(FToIRect(a.getGlobalBounds()));
	sf::IntRect boundsB(FToIRect(b.getGlobalBounds()));
	sf::IntRect intersection;

	if(boundsA.intersects(boundsB, intersection)) {
		const sf::Transform& inverseA(a.getInverseTransform());
		const sf::Transform& inverseB(b.getInverseTransform());

		const sf::Vector2u& sizeA(imgA.getSize());
		const sf::Vector2u& sizeB(imgB.getSize());

		const sf::Uint8* pixA = imgA.getPixelsPtr();
		const sf::Uint8* pixB = imgB.getPixelsPtr();

		sf::Vector2f vecA, vecB;
		int xMax = intersection.left + intersection.width;
		int yMax = intersection.top + intersection.height;

		for(int x = intersection.left; x < xMax; x++)
			for(int y = intersection.top; y < yMax; y++) {
				vecA = inverseA.transformPoint(x, y);
				vecB = inverseB.transformPoint(x, y);

				int idxA = ((int) vecA.x + ((int) vecA.y)*sizeA.x)*4 + 3;
				int idxB = ((int) vecB.x + ((int) vecB.y)*sizeB.x)*4 + 3;

				if(vecA.x > 0 && vecA.y > 0 &&
					 vecB.x > 0 && vecB.y > 0 &&
					 vecA.x < sizeA.x && vecA.y < sizeA.y &&
					 vecB.x < sizeB.x && vecB.y < sizeB.y &&
					 pixA[idxA] > 0 &&
					 pixB[idxB] > 0) {
					return 1;
				}
			}
	}

	return 0;
}