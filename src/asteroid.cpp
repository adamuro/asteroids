#include "asteroid.hpp"

asteroid::asteroid (sf::Vector2i windowPosition, sf::Vector2u windowSize, sf::Texture &asteroidTexture) {
	asteroidImage.setTexture(asteroidTexture);
	asteroidImage.setOrigin(75.0, 60.0);
	
	srand(time(0));
	const double mainSpeed = (double)(rand() % 10 + 6) / 100;
	const double sideSpeed = (double)(rand() % 10 + 6) / 100;
	const int direction = (rand() % 2) ? 1 : -1;
	const int side = rand() % 4;

	rotation = (double)(rand() % 4) / 10 * direction;

	switch(side) {
		case LEFT:
			position.x = windowPosition.x - 150.0;
			position.y = rand() % windowSize.y + windowPosition.y;
			speed.x = mainSpeed;
			speed.y = sideSpeed * direction;
			break;
		case RIGHT:
			position.x = windowPosition.x + windowSize.x;
			position.y = rand() % windowSize.y + windowPosition.y;
			speed.x = -mainSpeed;
			speed.y = sideSpeed * direction;
			break;
		case UP:
			position.x = rand() % windowSize.x + windowPosition.x;
			position.y = windowPosition.y - 120.0;
			speed.y = mainSpeed;
			speed.x = sideSpeed * direction;
			break;
		case DOWN:
			position.x = rand() % windowSize.x + windowPosition.x;
			position.y = windowPosition.y + windowSize.y;
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