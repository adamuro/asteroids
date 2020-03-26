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

	void run ();
	
	void drawAsteroids ();
	void drawBullets ();
	void drawShip ();

	bool offScreen(sf::Vector2f position);
	void keepShipOnScreen ();

	sf::IntRect FToIRect (const sf::FloatRect &f);
	bool collision (const sf::Sprite &a, const sf::Sprite &b, const sf::Image &imgA, const sf::Image &imgB);
private:
	const double windowWidth;
	const double windowHeight;
	sf::RenderWindow window;

	ship s {windowWidth / 2, windowHeight / 2};
	
	std::list<asteroid*> asteroids;
	sf::Texture asteroidTexture;

	std::vector<bullet> bullets;
	int bulletsAvailable;

	sf::Clock clock;
	int lastSecond;
};

#endif