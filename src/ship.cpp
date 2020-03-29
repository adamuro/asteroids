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
	if(acceleration) {
		shipAccelerateImage.setPosition(position);
		shipAccelerateImage.setRotation(rotation);
	}
	else {
		shipImage.setPosition(position);
		shipImage.setRotation(rotation);
	}
}

void ship::accelerate () {
	speed.x += 0.1 * sin(rotation * M_PI / 180.0);
	speed.y -= 0.1 * cos(rotation * M_PI / 180.0);
	acceleration = 1;
}

void ship::breaks () {
	speed.x *= 0.9995;
	speed.y *= 0.9995;
}

void ship::rotate (const int &direction) {
	if(direction == LEFT)
		rotation -= 4.0;
	if(direction == RIGHT)
		rotation += 4.0;
}

void ship::bounceVer () {
	speed.x *= -1.0;
}

void ship::bounceHor () {
	speed.y *= -1.0;
}

bullet* ship::shoot () {
	return new bullet(position, rotation, bulletTexture);
}

sf::Vector2f ship::getPosition () {
	return position;
}

sf::Sprite ship::getSprite () {
	return (acceleration) ? shipAccelerateImage : shipImage;
}

void ship::draw (sf::RenderWindow *window) {
	if(acceleration) {
		window->draw(shipAccelerateImage);
	}
	else {
		window->draw(shipImage);
	}
	acceleration = 0;
}