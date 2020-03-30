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

	void fly ();
	void draw (sf::RenderWindow &window);

	bool offScreen (sf::RenderWindow &window);

	sf::Sprite getSprite ();

	enum directions {UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3};
private:
	sf::Vector2f position;
	sf::Vector2f speed;
	double rotation;

	sf::Sprite asteroidSprite;
};

#endif