#include "ship.hpp"

ship::ship (double &&x, double &&y) {
	position.x = x;
	position.y = y;
	speed.x = 0;
	speed.y = 0;
	rotation = 0;

	bulletTexture.loadFromFile("./images/bullet.png");
	shipTexture.loadFromFile("./images/ship.png");
	shipImage.setTexture(shipTexture);
	shipImage.setOrigin(25.0, 25.0);
}

void ship::fly () {
	position += speed;
}

void ship::accelerate () {
	speed.x += 0.0002 * sin(rotation * M_PI / 180.0);
	speed.y -= 0.0002 * cos(rotation * M_PI / 180.0);
}

void ship::breaks () {
	speed.x *= 0.9995;
	speed.y *= 0.9995;
}

void ship::rotate (const int &direction) {
	if(direction == LEFT)
		rotation -= 0.2;
	if(direction == RIGHT)
		rotation += 0.2;
}

bullet ship::shoot () {
	return bullet(position, rotation, bulletTexture);
}

void ship::draw (sf::RenderWindow *window) {
	shipImage.setPosition(position);
	shipImage.setRotation(rotation);
	window->draw(shipImage);
}