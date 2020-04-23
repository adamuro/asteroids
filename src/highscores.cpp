#include "highscores.hpp"

highscores::highscores (sf::RenderWindow &window_): 
	windowSize(window_.getSize()),
	window(window_) {
	highscoresMainFont = sf::Font();
	highscoresMainFont.loadFromFile("./fonts/Starjedi.ttf");
	highscoresMainText = sf::Text();
	highscoresMainText.setString("Highscores");
	highscoresMainText.setFont(highscoresMainFont);
	highscoresMainText.setCharacterSize(150.0);
	highscoresMainText.setFillColor(sf::Color(sf::Color::White));
	highscoresMainText.setPosition(0.0, 100.0);
	centerText(highscoresMainText);

	generalFont = sf::Font();
	generalFont.loadFromFile("./fonts/BebasNeue-Regular.ttf");

	highscoresText = sf::Text();
	highscoresText.setFont(generalFont);
	highscoresText.setCharacterSize(40.0);
	highscoresText.setFillColor(sf::Color(sf::Color::White));
	loadHighscores();
}

void highscores::run () {
	while(window.isOpen()) { // Main loop
		sf::Event event;

		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed)
				window.close();
			if(event.type == sf::Event::KeyReleased) {
				if(event.key.code == sf::Keyboard::Return  ||
				  (event.key.code == sf::Keyboard::Escape) ||
				  (event.key.code == sf::Keyboard::Space)) {
					return;
				}
			}
		}
		window.clear();
		window.draw(highscoresMainText);
		drawHighscores();
		window.display();
	}
}

void highscores::drawHighscores () {
	for(int i = 0; i < 10; i++) {
		std::string standing = std::to_string(i + 1) + ". ";
		std::string nick = std::get<std::string>(highscoresVec[i]);
		int score = std::get<int>(highscoresVec[i]);
		double yResultPos = 350.0 + 50.0 * i;

		highscoresText.setString(standing + nick);
		highscoresText.setPosition(450.0, yResultPos);
		window.draw(highscoresText);
		
		highscoresText.setString(std::to_string(score));
		highscoresText.setPosition(860.0, yResultPos);
		window.draw(highscoresText);
	}
}

void highscores::loadHighscores () {
	std::ifstream highscoresFile;
	highscoresFile.open("highscores.txt");
	if(!highscoresFile.is_open()) {
		throw std::ios_base::failure("Highscores file opening failed.");
	}

	for(int i = 0; i < 10; i++) {
		std::string loadingNick;
		int loadingScore;

		highscoresFile >> loadingNick;
		highscoresFile >> loadingScore;

		std::pair<std::string, int> result;
		result = std::pair<std::string, int>(loadingNick, loadingScore);

		highscoresVec.push_back(result);
	}
	highscoresFile.close();
}

void highscores::centerText (sf::Text &text) {
	sf::FloatRect textRect = text.getGlobalBounds();
	double xTextPos = windowSize.x / 2 - textRect.width / 2;
	text.setPosition(xTextPos, text.getPosition().y);
}