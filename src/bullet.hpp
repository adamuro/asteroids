#ifndef BULLET_HPP
#define BULLET_HPP

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

class bullet {
public:
	bullet (sf::Vector2f spawn, double rotation, sf::Texture &bulletTexture);
	bullet () {}

	void fly ();
	void draw (sf::RenderWindow &window);

	bool offScreen (sf::RenderWindow &window);

	sf::Sprite getSprite ();
	sf::Image getImage ();
private:
	sf::Vector2f position;
	sf::Vector2f speed;

	sf::Sprite bulletSprite;
};

#endif