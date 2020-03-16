#include "ship.hpp"

ship::ship (double x, double y) {
	this->x = x;
	this->y = y;
	this->xSpeed = 0;
	this->ySpeed = 0;
	this->rotation = 0;

	this->shipTexture.loadFromFile("./images/ship.png");
	this->shipImage.setTexture(shipTexture);
	this->shipImage.setOrigin(25,25);
}

ship::ship (ship &s) {
	this->x = s.x;
	this->y = s.y;
	this->xSpeed = 0;
	this->ySpeed = 0;
	this->rotation = 0;

	this->shipTexture = s.shipTexture;
	this->shipImage.setTexture(shipTexture);
}

void ship::fly () {
	x += xSpeed;
	y += ySpeed;
}
void ship::accelerate () {
	xSpeed += 0.0002 * sin(rotation * M_PI / 180.0);
	ySpeed -= 0.0002 * cos(rotation * M_PI / 180.0);
}
void ship::breaks () {
	xSpeed *= 0.9995;
	ySpeed *= 0.9995;
}
void ship::rotate (const int &direction) {
	if(direction == LEFT)
		rotation -= 0.2;
	if(direction == RIGHT)
		rotation += 0.2;
}

void ship::draw (sf::RenderWindow *window) {
	shipImage.setPosition(x, y);
	shipImage.setRotation(rotation);
	window->draw(shipImage);
}