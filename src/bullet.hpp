#ifndef BULLET_HPP
#define BULLET_HPP

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

class bullet {
public:
	bullet (const double &rotation, const sf::Vector2f &spawnPoint, const sf::Texture &bulletTexture);
	bullet () {}

	void fly (); // Update position.
	void draw (sf::RenderWindow &window);

	bool offScreen (const sf::Vector2f &windowSize);

	sf::Sprite getSprite ();
private:
	sf::Vector2f position;
	sf::Vector2f speed;

	sf::Sprite bulletSprite;
};

#endif