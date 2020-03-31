#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <chrono>
#include <cstdint>

class asteroid {
public:
	asteroid (sf::Vector2u windowSize, sf::Texture &asteroidTexture);
	~asteroid () {}

	void fly (); // Update position.
	void draw (sf::RenderWindow &window);

	bool offScreen (const sf::Vector2f &windowSize);

	sf::Sprite getSprite ();

	enum directions {up = 0, down = 1, left = 2, right = 3};
private:
	sf::Vector2f position;
	sf::Vector2f speed;
	double rotation;

	sf::Sprite asteroidSprite;
};

#endif