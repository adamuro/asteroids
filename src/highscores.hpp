#ifndef HIGHSCORES_HPP
#define HIGHSCORES_HPP

#include <iostream>
#include <fstream>
#include <utility>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class highscores {
public:
	highscores (sf::RenderWindow &window);
	~highscores () {}

	void run ();

	void drawHighscores ();

	void loadHighscores ();

	void centerText (sf::Text &text);
private:
	const sf::Vector2f windowSize;
	sf::RenderWindow &window;

	sf::Text highscoresMainText;
	sf::Font highscoresMainFont;

	sf::Font generalFont;

	sf::Text highscoresText;
	std::vector<std::pair<std::string, int>> highscoresVec;
};

#endif