#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime>

class asteroid {
public:
	asteroid (sf::Vector2i windowPosition, sf::Vector2u windowSize, sf::Texture &asteroidTexture);
	~asteroid () {}

	void fly ();
	void draw (sf::RenderWindow *window);

	enum directions {UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3};
private:
	sf::Vector2f position;
	sf::Vector2f speed;
	double rotation;

	sf::Sprite asteroidImage;
};

#endif