#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "ship.hpp"
#include "asteroid.hpp"

class game {
public:
	game ();
	~game () {}
	void run ();

private:
	ship *s;
	asteroid *a;

	sf::RenderWindow window;
	sf::Vector2i windowPosition;
	sf::Vector2u windowSize;
};

#endif