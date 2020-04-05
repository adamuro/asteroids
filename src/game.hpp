#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "ship.hpp"
#include "asteroid.hpp"
#include "bullet.hpp"

class game {
public:
	game (sf::RenderWindow &window);
	~game ();

	int run ();
	
	void drawAsteroids ();
	void drawBullets ();
	void drawShip ();
	void drawScore ();
	void drawAvailableBullets ();

	void increaseScore (const int value);

	sf::IntRect FToIRect (const sf::FloatRect &f); // Auxilliary collision function.
	bool collision (const sf::Sprite &a, const sf::Sprite &b); // True if sprites' images 'touch' each other.
	bool checkCollisions (); // Delete off screen or colliding asteroids and bullets. True if ship was hit by asteroid.
private:
	const sf::Vector2f windowSize;
	sf::RenderWindow &window;

	ship s {windowSize};
	
	std::vector<asteroid*> asteroids;
	sf::Texture asteroidTexture;
	double asteroidsRespTime;

	std::vector<bullet*> bullets;
	sf::Texture bulletTexture;
	sf::Sprite bulletSprite;
	double reloadTime;

	sf::Clock asteroidsClock;
	sf::Clock bulletsClock;
	sf::Clock gameClock;

	int score;
	sf::Text scoreText;
	sf::Font scoreFont;
};

#endif