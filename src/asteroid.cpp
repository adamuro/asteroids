#include "asteroid.hpp"

asteroid::asteroid (sf::Vector2u windowSize, sf::Texture &asteroidTexture) {
	asteroidSprite.setTexture(asteroidTexture);
	asteroidSprite.setOrigin(75.0, 60.0);
	
	const auto systemTime = std::chrono::system_clock::now();
	const auto epochTime = systemTime.time_since_epoch();
	const auto timeMillisec = std::chrono::duration_cast<std::chrono::milliseconds>(epochTime);
	const int seed = timeMillisec.count();
	srand(seed);

	const double mainSpeed = (double)(rand() % 10 + 6) / 8;
	const double sideSpeed = (double)(rand() % 10 + 6) / 8;
	const int direction = (rand() % 2) ? 1 : -1;
	const int side = rand() % 4;

	rotation = (double)(rand() % 4) / 10 * direction;

	switch(side) {
		case LEFT:
			position.x = 0;
			position.y = rand() % (int)windowSize.y;
			speed.x = mainSpeed;
			speed.y = sideSpeed * direction;
			break;
		case RIGHT:
			position.x = windowSize.x;
			position.y = rand() % (int)windowSize.y;
			speed.x = -mainSpeed;
			speed.y = sideSpeed * direction;
			break;
		case UP:
			position.x = rand() % (int)windowSize.x;
			position.y = 0;
			speed.y = mainSpeed;
			speed.x = sideSpeed * direction;
			break;
		case DOWN:
			position.x = rand() % (int)windowSize.x;
			position.y = windowSize.y;
			speed.y = -mainSpeed;
			speed.x = sideSpeed * direction;
			break;
	}
}

void asteroid::fly () {
	position += speed;
}

void asteroid::draw (sf::RenderWindow &window) {
	asteroidSprite.setPosition(position);
	asteroidSprite.setRotation(asteroidSprite.getRotation() + rotation);
	window.draw(asteroidSprite);
}

bool asteroid::offScreen (sf::RenderWindow &window) {
	return (position.x > window.getSize().x + 150  ||
		   (position.x < -150)	    		     	||
	  	   (position.y > window.getSize().y + 150) ||
	  	   (position.y < -150));
}


sf::Sprite asteroid::getSprite () {
	return asteroidSprite;
}