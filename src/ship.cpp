#include "ship.hpp"

ship::ship (const sf::Vector2f windowSize) {
	position.x = windowSize.x / 2;
	position.y = windowSize.y / 2;
	speed.x = 0;
	speed.y = -1;
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
	if(direction == left)
		rotation -= 4.0;
	if(direction == right)
		rotation += 4.0;
}

void ship::bounceVer () {
	speed.x *= -1.0;
}

void ship::bounceHor () {
	speed.y *= -1.0;
}

void ship::stayOnScreen (const sf::Vector2f &windowSize) {
	if(position.x > windowSize.x - 14.0 ||
	  (position.x < 16.0)) {
		bounceVer();
	}
	if(position.y > windowSize.y - 14.0 ||
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

int ship::getBulletsNum () {
	return bulletsAvailable;
}

void ship::load () {
	bulletsAvailable++;
}

bullet* ship::shoot () {
	bulletsAvailable--;
	return new bullet(rotation, position, bulletTexture);
}

sf::Vector2f ship::getPosition () {
	return position;
}

sf::Sprite ship::getSprite () {
	return shipSprite;
}

void ship::draw (sf::RenderWindow &window) {
	if(acceleration)
		window.draw(shipAccelerateSprite);
	else
		window.draw(shipSprite);

	acceleration = 0;
}