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
	void bounceVer ();
	void bounceHor ();
	bullet* shoot ();

	sf::Vector2f getPosition ();
	sf::Sprite getSprite ();

	enum directions {LEFT = 0, RIGHT = 1};
private:
	sf::Vector2f position;
	sf::Vector2f speed;
	double rotation;
	bool acceleration;

	sf::Texture bulletTexture;

	sf::Texture shipTexture;
	sf::Texture shipAccelerateTexture;
	sf::Sprite shipImage;
	sf::Sprite shipAccelerateImage;
};

#endif