#include "asteroid.hpp"

asteroid::asteroid (sf::Vector2u windowSize, sf::Texture &asteroidTexture) {
	asteroidSprite.setTexture(asteroidTexture);
	asteroidSprite.setOrigin(75.0, 60.0);
	
	const int seed = generateSeed();
	srand(seed);

	const double mainSpeed = (double)(rand() % 15 + 5) / 8;
	const double sideSpeed = (double)(rand() % 25 + 5) / 8;
	const int direction = (rand() % 2) ? 1 : -1;
	const int side = rand() % 4;

	rotation = (rand() % 4) * direction;

	switch(side) {
		case left:
			position.x = -150.0;
			position.y = rand() % (int)windowSize.y;
			speed.x = mainSpeed;
			speed.y = sideSpeed * direction;
			break;
		case right:
			position.x = windowSize.x + 150.0;
			position.y = rand() % (int)windowSize.y;
			speed.x = -mainSpeed;
			speed.y = sideSpeed * direction;
			break;
		case up:
			position.x = rand() % (int)windowSize.x;
			position.y = -150.0;
			speed.y = mainSpeed;
			speed.x = sideSpeed * direction;
			break;
		case down:
			position.x = rand() % (int)windowSize.x;
			position.y = windowSize.y + 150.0;
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

bool asteroid::offScreen (const sf::Vector2f &windowSize) {
	return (position.x > windowSize.x + 150  ||
		   (position.x < -150)	    		 ||
	  	   (position.y > windowSize.y + 150) ||
	  	   (position.y < -150));
}


sf::Sprite asteroid::getSprite () {
	return asteroidSprite;
}

const int asteroid::generateSeed () {
	const auto systemTime = std::chrono::system_clock::now();
	const auto epochTime = systemTime.time_since_epoch();
	const auto timeMillisec = std::chrono::duration_cast<std::chrono::milliseconds>(epochTime);
	const int seed = timeMillisec.count();
	return seed;
}