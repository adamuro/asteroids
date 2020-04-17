#include "game.hpp"

game::game (sf::RenderWindow &window_): 
	windowSize(window_.getSize()),
	window(window_) {
	gameClock = sf::Clock();

	asteroidTexture.loadFromFile("./images/asteroid1.png");
	asteroidsClock = sf::Clock();
	asteroidsRespTime = 0.5;

	bulletTexture.loadFromFile("./images/bullet.png");
	bulletSprite.setTexture(bulletTexture);
	bulletSprite.setPosition(50.0, windowSize.y - 50.0);
	bulletsClock = sf::Clock();
	reloadTime = 1.0;

	scoreFont = sf::Font();
	scoreFont.loadFromFile("./fonts/BebasNeue-Regular.ttf");
	scoreText = sf::Text();
	scoreText.setFont(scoreFont);
	scoreText.setCharacterSize(40.0);
	scoreText.setFillColor(sf::Color(sf::Color::White));
	score = 10.0;
}

game::~game () {
	for(asteroid *a: asteroids)
		delete a;
	for(bullet *b: bullets)
		delete b;
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
						if(s.magazineFull())
							bulletsClock.restart();
						bullets.push_back(s.shoot());
					}
				}
			}
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
		  (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
			s.rotate(ship::left);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
		  (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) 
			s.rotate(ship::right);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
		  (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
			s.accelerate();
		if(checkCollisions())
			return score;

		if(asteroidsClock.getElapsedTime().asSeconds() > asteroidsRespTime) {
			increaseScore(10.0);
			asteroidsClock.restart();
			asteroids.push_back(new asteroid(windowSize, asteroidTexture));
		}
		if(bulletsClock.getElapsedTime().asSeconds() > reloadTime) {
			if(!s.magazineFull()) {
				s.load();
				bulletsClock.restart();
			}
		}
		if(gameClock.getElapsedTime().asSeconds() > 1) {
			gameClock.restart();
			if(asteroidsRespTime > 0.1) {
				asteroidsRespTime -= 0.0025;
			}
		}

		window.clear();
		drawBullets();
		drawShip();
		drawAsteroids();
		drawScore();
		drawAvailableBullets();
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
	s.stayOnScreen(windowSize);
	s.fly();
	s.draw(window);
}

void game::drawScore () {
	double distFromRightBorder = 16.0 * (int)log10(score) + 130.0;
	double xScorePosition = windowSize.x - distFromRightBorder;
	double yScorePosition = windowSize.y - 60.0;

	scoreText.setPosition(xScorePosition, yScorePosition);
	scoreText.setString("Score: " + std::to_string(score));

	window.draw(scoreText);
}

void game::drawAvailableBullets () {
	sf::RectangleShape bulletField(sf::Vector2f(10.0, 10.0));
	double yFieldPosition = windowSize.y - 60.0;

	for(int i = 0; i < 10; i++) {
		double xFieldPosition = 10.0 + i * 15.0;
		bulletField.setPosition(xFieldPosition, yFieldPosition);

		if(s.getBulletsNum() > i)
			bulletField.setFillColor(sf::Color(sf::Color::Green));
		else
			bulletField.setFillColor(sf::Color(sf::Color::Red));

		window.draw(bulletField);
	}
	window.draw(bulletSprite);
}

void game::increaseScore (const int value) {
	score += value;
}

sf::IntRect game::FToIRect (const sf::FloatRect& f) {
	return sf::IntRect((int) f.left, (int) f.top, (int) f.width, (int) f.height);
}

bool game::collision (const sf::Sprite &a, const sf::Sprite &b) {
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
			if(bullets[b]->offScreen(windowSize)) {
				delete bullets[b];
				bullets.erase(bullets.begin() + b);
			}
			else if(a < asteroids.size()) { 
				if(collision(bullets[b]->getSprite(), asteroids[a]->getSprite())) {
					delete bullets[b];
					delete asteroids[a];
					bullets.erase(bullets.begin() + b);
					asteroids.erase(asteroids.begin() + a);
					increaseScore(50.0);
				}
			}
		}
		if(a < asteroids.size()) {
			if(asteroids[a]->offScreen(windowSize)) {
				delete asteroids[a];
				asteroids.erase(asteroids.begin() + a);
			}
			else if(collision(s.getSprite(), asteroids[a]->getSprite())) {
				system("sleep 1");
				return 1;
			}
}
	}
	return 0;
}