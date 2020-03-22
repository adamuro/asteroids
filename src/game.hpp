#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "ship.hpp"
#include "asteroid.hpp"
#include "bullet.hpp"

class game {
public:
	game ();
	~game () {}

	void run ();
	void drawAsteroids ();
	void drawBullets ();
	void drawShip ();
private:
	const double windowWidth;
	const double windowHeight;
	sf::RenderWindow window;

	ship s {windowWidth / 2, windowHeight / 2};
	
	std::vector<asteroid> asteroids;
	sf::Texture asteroidTexture;

	std::vector<bullet> bullets;
	int bulletsAvailable;

	sf::Clock clock;
	int lastSecond;
};

#endif