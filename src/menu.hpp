#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class menu {
public:
	menu (sf::RenderWindow &window);
	~menu () {}

	int run ();

	void drawOptions ();

	void centerText (sf::Text &text);

	enum options {play, highscores, exit};
private:
	const sf::Vector2f windowSize;
	sf::RenderWindow &window;

	sf::Text asteroidsText;
	sf::Font asteroidsFont;

	std::string optionsString [3];
	sf::Text optionsText [3];
	sf::Font optionsFont;

	int choice;
};

#endif