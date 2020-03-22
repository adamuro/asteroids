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
	void draw (sf::RenderWindow *window);
private:
	sf::Vector2f position;
	sf::Vector2f speed;

	sf::Sprite bulletImage;
};

#endif