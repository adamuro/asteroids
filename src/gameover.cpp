#include "gameover.hpp"

gameover::gameover (sf::RenderWindow &window_, const int score): 
	windowSize(window_.getSize()),
	window(window_) {
	gameOverFont = sf::Font();
	gameOverFont.loadFromFile("./fonts/Starjedi.ttf");
	gameOverText = sf::Text();
	gameOverText.setString("Game Over");
	gameOverText.setFont(gameOverFont);
	gameOverText.setCharacterSize(150.0);
	gameOverText.setFillColor(sf::Color(sf::Color::White));
	gameOverText.setPosition(0.0, 100.0);
	centerText(gameOverText);

	generalFont = sf::Font();
	generalFont.loadFromFile("./fonts/BebasNeue-Regular.ttf");

	scoreText = sf::Text();
	scoreText.setString("Score: " + std::to_string(score));
	scoreText.setFont(generalFont);
	scoreText.setCharacterSize(50.0);
	scoreText.setFillColor(sf::Color(sf::Color::White));
	scoreText.setPosition(0.0, 200.0);
	centerText(scoreText);

	highscoresText = sf::Text();
	highscoresText.setFont(generalFont);
	highscoresText.setCharacterSize(30.0);
	highscoresText.setFillColor(sf::Color(sf::Color::White));

	loadHighscores();

	nick = "";
}

int gameover::run () {
	while(window.isOpen()) { // Main loop
		sf::Event event;

		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed)
				window.close();
			if(event.type == sf::Event::KeyReleased) {
				if(event.key.code == sf::Keyboard::Return) {
					return 0;
				}
			}
		}
		window.clear();
		drawHighscores();
		
		window.display();
	}
	return -1; // Error
}

void gameover::drawHighscores () {
	for(int i = 0; i < 10; i++) {
		std::string standing = std::to_string(i + 1) + ". ";
		std::string nick = std::get<std::string>(highscores.at(i));
		int score = std::get<int>(highscores.at(i));
		double yRecordPos = 300.0 + 40.0 * i;

		highscoresText.setString(standing + nick);
		highscoresText.setPosition(420.0, yRecordPos);
		window.draw(highscoresText);
		
		highscoresText.setString(std::to_string(score));
		highscoresText.setPosition(860.0, yRecordPos);
		window.draw(highscoresText);
	}
}

void gameover::loadHighscores () {
	std::ifstream highscoresFile;
	highscoresFile.open("highscores");
	if(!highscoresFile.is_open()) {
		throw std::ios_base::failure("Highscores file opening failed.");
	}

	for(int i = 0; i < 10; i++) {
		std::string loadingNick;
		int loadingScore;

		highscoresFile >> loadingNick;
		highscoresFile >> loadingScore; // 860

		std::pair<std::string, int> record;
		record = std::pair<std::string, int>(loadingNick, loadingScore);

		highscores.push_back(record);
	}
	highscoresFile.close();
}

void gameover::centerText (sf::Text &text) {
	sf::FloatRect textRect = text.getGlobalBounds();
	double xTextPos = windowSize.x / 2 - textRect.width / 2;
	text.setPosition(xTextPos, text.getPosition().y);
}