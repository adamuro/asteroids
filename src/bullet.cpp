#include "bullet.hpp"

bullet::bullet (sf::Vector2f spawn, double rotation, sf::Texture &bulletTexture) {
	bulletImage.setTexture(bulletTexture);
	bulletImage.setOrigin(25.0, 25.0);
	bulletImage.setRotation(rotation + 90.0);

	speed.x += 5 * sin(rotation * M_PI / 180.0);
	speed.y -= 5 * cos(rotation * M_PI / 180.0);

	position.x = spawn.x + speed.x * 5;
	position.y = spawn.y + speed.y * 5;
}

void bullet::fly () {
	position += speed;
}

void bullet::draw (sf::RenderWindow *window) {
	bulletImage.setPosition(position);
	window->draw(bulletImage);
}

bool bullet::offScreen (sf::RenderWindow *window) {
	return (position.x > window->getSize().x + 50  ||
		   (position.x < -50)	 		     	   ||
	  	   (position.y > window->getSize().y + 50) ||
	  	   (position.y < -50));
}

sf::Sprite bullet::getSprite () {
	return bulletImage;
}