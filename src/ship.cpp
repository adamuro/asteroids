#include "ship.hpp"

ship::ship (double &&x, double &&y) {
	position.x = x;
	position.y = y;
	speed.x = 0;
	speed.y = 0;
	rotation = 0;
	acceleration = 0;
	bulletsAvailable = 0;

	bulletTexture.loadFromFile("./images/bullet.png");
	shipTexture.loadFromFile("./images/ship.png");
	shipSprite.setTexture(shipTexture);
	shipSprite.setOrigin(30.0, 30.0);
	shipAccelerateTexture.loadFromFile("./images/shipAccelerate.png");
	shipAccelerateSprite.setTexture(shipAccelerateTexture);
	shipAccelerateSprite.setOrigin(30.0, 30.0);
}

void ship::fly () {
	position += speed;
	shipAccelerateSprite.setPosition(position);
	shipAccelerateSprite.setRotation(rotation);
	shipSprite.setPosition(position);
	shipSprite.setRotation(rotation);
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

void ship::load () {
	bulletsAvailable++;
}

void ship::bounceVer () {
	speed.x *= -1.0;
}

void ship::bounceHor () {
	speed.y *= -1.0;
}

void ship::stayOnScreen (sf::RenderWindow &window) {
	if(position.x > window.getSize().x - 14.0 ||
	  (position.x < 16.0)) {
		bounceVer();
	}
	if(position.y > window.getSize().y - 14.0 ||
	  (position.y < 16.0)) {
		bounceHor();
	}
}

bool ship::magazineFull () {
	return (bulletsAvailable == 10);
}

bool ship::magazineEmpty () {
	return (bulletsAvailable == 0);
}

bullet* ship::shoot () {
	bulletsAvailable--;
	return new bullet(position, rotation, bulletTexture);
}

sf::Vector2f ship::getPosition () {
	return position;
}

sf::Sprite ship::getSprite () {
	return (acceleration) ? shipAccelerateSprite : shipSprite;
}

void ship::draw (sf::RenderWindow &window) {
	if(acceleration) {
		window.draw(shipAccelerateSprite);
	}
	else {
		window.draw(shipSprite);
	}
	acceleration = 0;
}