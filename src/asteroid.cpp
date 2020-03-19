#include "asteroid.hpp"

asteroid::asteroid (sf::Vector2i windowPosition, sf::Vector2u windowSize, sf::Texture &asteroidTexture) {
	asteroidImage.setTexture(asteroidTexture);
	asteroidImage.setOrigin(75.0, 60.0);
	
	srand(time(0));
	int side = rand() % 4;
	int direction = (rand() % 2) ? 1 : -1;
	rotation = (double)(rand() % 4) / 10 * direction;

	switch(side) {
		case UP:
			x = windowPosition.x - 150.0;
			y = rand() % windowSize.y + windowPosition.y;
			xSpeed = 0.1;
			ySpeed = (double)(rand() % 3) / 10 * direction;
			break;
		case DOWN:
			x = windowPosition.x + windowSize.x;
			y = rand() % windowSize.y + windowPosition.y;
			xSpeed = -0.1;
			ySpeed = (double)(rand() % 3) / 10 * direction;
			break;
		case LEFT:
			x = rand() % windowSize.x + windowPosition.x;
			y = windowPosition.y - 120.0;
			ySpeed = 0.1;
			xSpeed = (double)(rand() % 3) / 10 * direction;
			break;
		case RIGHT:
			x = rand() % windowSize.x + windowPosition.x;
			y = windowPosition.y + windowSize.y;
			ySpeed = -0.1;
			xSpeed = (double)(rand() % 3) / 10 * direction;
			break;
	}
}

void asteroid::fly () {
	x += xSpeed;
	y += ySpeed;
}

void asteroid::draw (sf::RenderWindow *window) {
	asteroidImage.setPosition(sf::Vector2f(x, y));
	asteroidImage.setRotation(asteroidImage.getRotation() + rotation);
	window->draw(asteroidImage);
}