#include "bullet.hpp"

bullet::bullet (sf::Vector2f spawn, double rotation, sf::Texture &bulletTexture) {
	bulletImage.setTexture(bulletTexture);
	bulletImage.setOrigin(25.0, 25.0);
	bulletImage.setRotation(rotation + 90.0);

	speed.x += 0.25 * sin(rotation * M_PI / 180.0);
	speed.y -= 0.25 * cos(rotation * M_PI / 180.0);

	position.x = spawn.x + speed.x * 100;
	position.y = spawn.y + speed.y * 100;
}

void bullet::fly () {
	position += speed;
}

void bullet::draw (sf::RenderWindow *window) {
	bulletImage.setPosition(position);
	window->draw(bulletImage);
}