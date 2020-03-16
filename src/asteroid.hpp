#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <random>

class asteroid {
public:
	asteroid (sf::Vector2i windowPosition, sf::Vector2u windowSize);
	~asteroid () {}

	void fly ();
	void draw (sf::RenderWindow *window);
private:
	double x;
	double y;
	double speed_x;
	double speed_y;

	sf::Texture asteroidTexture;
	sf::Sprite asteroidImage;
};

#endif