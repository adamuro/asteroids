#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "ship.hpp"
#include "asteroid.hpp"

class game {
public:
	game ();
	~game () {}

	void run ();
	void drawAsteroids ();

private:
	ship s = ship(640.0, 480.0);
	std::vector<asteroid> asteroids;
	sf::Texture asteroidTexture;

	sf::RenderWindow window;
	sf::Vector2i windowPosition;
	sf::Vector2u windowSize;

	sf::Clock clock;
	int lastAsteroidTime;
};

#endif