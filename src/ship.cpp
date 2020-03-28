#include "ship.hpp"

ship::ship (double &&x, double &&y) {
	position.x = x;
	position.y = y;
	speed.x = 0;
	speed.y = 0;
	rotation = 0;
	acceleration = 0;

	bulletTexture.loadFromFile("./images/bullet.png");
	shipTexture.loadFromFile("./images/ship.png");
	shipImage.setTexture(shipTexture);
	shipImage.setOrigin(30.0, 30.0);
	shipAccelerateTexture.loadFromFile("./images/shipAccelerate.png");
	shipAccelerateImage.setTexture(shipAccelerateTexture);
	shipAccelerateImage.setOrigin(30.0, 30.0);
}

void ship::fly () {
	position += speed;
}

void ship::accelerate () {
	speed.x += 0.05 * sin(rotation * M_PI / 180.0);
	speed.y -= 0.05 * cos(rotation * M_PI / 180.0);
	acceleration = 1;
}

void ship::breaks () {
	speed.x *= 0.9995;
	speed.y *= 0.9995;
}

void ship::rotate (const int &direction) {
	if(direction == LEFT)
		rotation -= 3.0;
	if(direction == RIGHT)
		rotation += 3.0;
}

void ship::bounceVer () {
	speed.x *= -1;
}

void ship::bounceHor () {
	speed.y *= -1;
}

bullet* ship::shoot () {
	return new bullet(position, rotation, bulletTexture);
}

sf::Vector2f ship::getPosition () {
	return position;
}

sf::Sprite ship::getSprite () {
	return shipImage;
}

void ship::draw (sf::RenderWindow *window) {
	if(acceleration) {
		shipAccelerateImage.setPosition(position);
		shipAccelerateImage.setRotation(rotation);
		window->draw(shipAccelerateImage);
		acceleration = 0;
	}
	else {
		shipImage.setPosition(position);
		shipImage.setRotation(rotation);
		window->draw(shipImage);
	}
}