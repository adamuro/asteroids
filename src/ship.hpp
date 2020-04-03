#ifndef SHIP_HPP
#define SHIP_HPP

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "bullet.hpp"

class ship {
public:
	ship (const sf::Vector2f windowSize);
	~ship () {};

	void draw (sf::RenderWindow &window);
	
	void fly (); // Update position.
	void accelerate ();
	void breaks ();
	void rotate (const int &direction);
	void bounceVer (); // Two auxilliary
	void bounceHor (); // stayOnScreen functions.
	void stayOnScreen (const sf::Vector2f &windowSize); // Bouncing off the screen borders.
	bool magazineFull ();
	bool magazineEmpty ();
	int getBulletsNum ();
	void load ();
	bullet* shoot ();

	sf::Vector2f getPosition ();
	sf::Sprite getSprite ();

	enum directions {left = 0, right = 1};
private:
	sf::Vector2f position;
	sf::Vector2f speed;
	double rotation;
	bool acceleration;
	int bulletsAvailable;

	sf::Texture shipTexture;
	sf::Texture shipAccelerateTexture;
	sf::Sprite shipSprite;
	sf::Sprite shipAccelerateSprite;

	sf::Texture bulletTexture;
};

#endif