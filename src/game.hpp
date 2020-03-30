#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "ship.hpp"
#include "asteroid.hpp"
#include "bullet.hpp"

class game {
public:
	game ();
	~game () {}

	int run ();
	
	void drawAsteroids ();
	void drawBullets ();
	void drawShip ();

	void increaseScore (int value);

	sf::IntRect FToIRect (const sf::FloatRect &f);
	bool collision (const sf::Sprite &a, const sf::Sprite &b);
	bool checkCollisions ();
private:
	const double windowWidth;
	const double windowHeight;
	sf::RenderWindow window;

	ship s {windowWidth / 2, windowHeight / 2};
	
	std::vector<asteroid*> asteroids;
	sf::Texture asteroidTexture;

	std::vector<bullet*> bullets;
	// Vector for drawing available bullets.

	sf::Clock clock;
	// Need to make separate clocks for asteroids and bullets.
	int score;
	// Something to draw score.
};

#endif