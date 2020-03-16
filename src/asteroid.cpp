#include "asteroid.hpp"

asteroid::asteroid (sf::Vector2i windowPosition, sf::Vector2u windowSize) {
	asteroidTexture.loadFromFile("./images/asteroid1.png");
	asteroidImage.setTexture(asteroidTexture);
	asteroidImage.setOrigin(75.0, 60.0);
	
	srand(time(0));
	int side = rand() % 4;

	switch(side) {
		case 0:
			x = windowPosition.x;
			y = rand() % windowSize.y + windowPosition.y;
			speed_x = 0.1;
			speed_y = 0;
			break;
		case 1:
			x = windowPosition.x + windowSize.x;
			y = rand() % windowSize.y + windowPosition.y;
			speed_x = -0.1;
			speed_y = 0;
			break;
		case 2:
			x = rand() % windowSize.x + windowPosition.x;
			y = windowPosition.y;
			speed_y = 0.1;
			speed_x = 0;
			break;
		case 3:
			x = rand() % windowSize.x + windowPosition.x;
			y = windowPosition.y + windowSize.y;
			speed_y = -0.1;
			speed_x = 0;
			break;
	}
}

void asteroid::fly () {
	x += speed_x;
	y += speed_y;
}

void asteroid::draw (sf::RenderWindow *window) {
	asteroidImage.setPosition(sf::Vector2f(x, y));
	window->draw(asteroidImage);
}