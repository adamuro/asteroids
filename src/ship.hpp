#ifndef SHIP_HPP
#define SHIP_HPP

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

class ship {
public:
	ship (double &&x, double &&y);
	~ship () {};

	void fly ();
	void accelerate ();
	void breaks ();
	void rotate (const int &direction);
	enum directions {LEFT = 0, RIGHT = 1};

	void draw (sf::RenderWindow *window);
private:
	double x;
	double y;
	double xSpeed;
	double ySpeed;
	double rotation;

	sf::Texture shipTexture;
	sf::Sprite shipImage;
};

#endif