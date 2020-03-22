#ifndef SHIP_HPP
#define SHIP_HPP

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "bullet.hpp"

class ship {
public:
	ship (double &&x, double &&y);
	~ship () {};

	void draw (sf::RenderWindow *window);
	
	void fly ();
	void accelerate ();
	void breaks ();
	void rotate (const int &direction);
	bullet shoot ();

	enum directions {LEFT = 0, RIGHT = 1};
private:
	sf::Vector2f position;
	sf::Vector2f speed;
	double rotation;

	sf::Texture bulletTexture;

	sf::Texture shipTexture;
	sf::Sprite shipImage;
};

#endif