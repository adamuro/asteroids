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

	void draw (sf::RenderWindow &window);
	
	void fly ();
	void accelerate ();
	void breaks ();
	void rotate (const int &direction);
	void load ();
	void bounceVer ();
	void bounceHor ();
	void stayOnScreen (sf::RenderWindow &window);
	bool magazineFull ();
	bool magazineEmpty ();
	bullet* shoot ();

	sf::Vector2f getPosition ();
	sf::Sprite getSprite ();
	sf::Image getImage ();

	enum directions {LEFT = 0, RIGHT = 1};
private:
	sf::Vector2f position;
	sf::Vector2f speed;
	double rotation;
	bool acceleration;
	int bulletsAvailable;

	sf::Texture bulletTexture;

	sf::Texture shipTexture;
	sf::Texture shipAccelerateTexture;
	sf::Sprite shipSprite;
	sf::Sprite shipAccelerateSprite;
};

#endif