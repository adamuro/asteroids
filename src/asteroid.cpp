#include "asteroid.hpp"

asteroid::asteroid (sf::Vector2u windowSize, sf::Texture &asteroidTexture) {
	asteroidImage.setTexture(asteroidTexture);
	asteroidImage.setOrigin(75.0, 60.0);
	
	srand(time(0));
	const double mainSpeed = (double)(rand() % 10 + 6) / 10;
	const double sideSpeed = (double)(rand() % 10 + 6) / 10;
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

void asteroid::draw (sf::RenderWindow *window) {
	asteroidImage.setPosition(position);
	asteroidImage.setRotation(asteroidImage.getRotation() + rotation);
	window->draw(asteroidImage);
}

sf::Vector2f asteroid::getPosition () {
	return position;
}