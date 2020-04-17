#ifndef GAMEOVER_HPP
#define GAMEOVER_HPP

#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class gameover {
public:
	gameover (sf::RenderWindow &window, const int score);
	~gameover () {}

	int run ();

	void drawScore ();
	void drawHighscores ();
	void drawNick ();

	void loadHighscores ();

	void editNick (int keyCode);
	void centerText (sf::Text &text);
	bool isLetterAscii (char keyCode);
private:
	const sf::Vector2f windowSize;
	sf::RenderWindow &window;

	sf::Text gameOverText;
	sf::Font gameOverFont;

	sf::Font generalFont;

	sf::Text scoreText;

	sf::Text highscoresText;
	std::vector<std::pair<std::string, int>> highscores;

	sf::Text enterNickText;
	sf::Text nickText;
	std::string nick;
};

#endif