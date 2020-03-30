#include "game.hpp"

game::game (): windowWidth(1280.0), windowHeight(960.0) {
	window.create(sf::VideoMode(windowWidth, windowHeight), "Asteroids");
	window.setFramerateLimit(60.0);
	asteroidTexture.loadFromFile("./images/asteroid1.png");
	clock = sf::Clock();
	score = 0;
}

int game::run () {
	while(window.isOpen()) { // Main loop
		sf::Event event;

		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed)
				window.close();
			if(event.type == sf::Event::KeyReleased) {
				if(event.key.code == sf::Keyboard::Space) {
					if(!s.magazineEmpty()) {
						bullets.push_back(s.shoot());
					}
				}
			}
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			s.rotate(ship::LEFT);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
			s.rotate(ship::RIGHT);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			s.accelerate();
		if(checkCollisions())
			return score;

		if(clock.getElapsedTime().asSeconds() > 0.5) {
			increaseScore(10);
			clock.restart();
			asteroids.push_back(new asteroid(window.getSize(), asteroidTexture));
			
			// Put it in separate if to make loading slower
			if(!s.magazineFull())
				s.load();
		}
		
		window.clear();
		drawBullets();
		drawShip();
		drawAsteroids();
		window.display();
	}
	return -1; // Error
}

void game::drawAsteroids () {
	for(asteroid *a: asteroids) {
		a->fly();
		a->draw(window);
	}
}

void game::drawBullets () {
	for(bullet *b: bullets) {
		b->fly();
		b->draw(window);
	}
}

void game::drawShip () {
	s.stayOnScreen(window);
	s.fly();
	s.draw(window);
}

void game::increaseScore (int value) {
	score += value;
}

sf::IntRect game::FToIRect(const sf::FloatRect& f) {
	return sf::IntRect((int) f.left, (int) f.top, (int) f.width, (int) f.height);
}

bool game::collision(const sf::Sprite &a, const sf::Sprite &b) {
	sf::IntRect boundsA(FToIRect(a.getGlobalBounds()));
	sf::IntRect boundsB(FToIRect(b.getGlobalBounds()));
	sf::IntRect intersection;

	const sf::Image imgA = a.getTexture()->copyToImage();
	const sf::Image imgB = b.getTexture()->copyToImage();

	if(boundsA.intersects(boundsB, intersection)) {
		const sf::Transform &inverseA(a.getInverseTransform());
		const sf::Transform &inverseB(b.getInverseTransform());

		const sf::Vector2u &sizeA(imgA.getSize());
		const sf::Vector2u &sizeB(imgB.getSize());

		const sf::Uint8 *pixA = imgA.getPixelsPtr();
		const sf::Uint8 *pixB = imgB.getPixelsPtr();

		sf::Vector2f vecA, vecB;
		const int xMax = intersection.left + intersection.width;
		const int yMax = intersection.top + intersection.height;

		for(int x = intersection.left; x < xMax; x++) {
			for(int y = intersection.top; y < yMax; y++) {
				vecA = inverseA.transformPoint(x, y);
				vecB = inverseB.transformPoint(x, y);

				int idxA = ((int) vecA.x + ((int) vecA.y) * sizeA.x) * 4 + 3;
				int idxB = ((int) vecB.x + ((int) vecB.y) * sizeB.x) * 4 + 3;

				if(vecA.x > 0 && vecA.y > 0  &&
				  (vecB.x > 0 && vecB.y > 0) &&
				  (vecA.x < sizeA.x && vecA.y < sizeA.y) &&
				  (vecB.x < sizeB.x && vecB.y < sizeB.y) &&
				  (pixA[idxA] > 0 && pixB[idxB] > 0)) {
					return 1;
				}
			}
		}
	}
	return 0;
}

bool game::checkCollisions () {
	for(uint a = 0; a < asteroids.size(); a++) {
		for(uint b = 0; b < bullets.size(); b++) {
			if(bullets[b]->offScreen(window)) {
				delete bullets[b];
				bullets.erase(bullets.begin() + b);
			}
			else if(a < asteroids.size()) { 
				if(collision(bullets[b]->getSprite(), asteroids[a]->getSprite())) {
					delete bullets[b];
					delete asteroids[a];
					bullets.erase(bullets.begin() + b);
					asteroids.erase(asteroids.begin() + a);
					increaseScore(50);
				}
			}
		}
		if(a < asteroids.size()) {
			if(asteroids[a]->offScreen(window)) {
				delete asteroids[a];
				asteroids.erase(asteroids.begin() + a);
			}
			else if(collision(s.getSprite(), asteroids[a]->getSprite())) {
				return 1;
			}
}
	}
	return 0;
}