#include "gameover.hpp"

gameover::gameover (sf::RenderWindow &window_, const int score_): 
	windowSize(window_.getSize()),
	window(window_),
	score(score_) {
	gameOverFont = sf::Font();
	gameOverFont.loadFromFile("./fonts/Starjedi.ttf");
	gameOverText = sf::Text();
	gameOverText.setString("Game over");
	gameOverText.setFont(gameOverFont);
	gameOverText.setCharacterSize(130.0);
	gameOverText.setFillColor(sf::Color(sf::Color::White));
	gameOverText.setPosition(0.0, 70.0);
	centerText(gameOverText);

	generalFont = sf::Font();
	generalFont.loadFromFile("./fonts/BebasNeue-Regular.ttf");

	scoreText = sf::Text();
	scoreText.setString("Score: " + std::to_string(score));
	scoreText.setFont(generalFont);
	scoreText.setCharacterSize(70.0);
	scoreText.setFillColor(sf::Color(sf::Color::White));
	scoreText.setPosition(0.0, 250.0);
	centerText(scoreText);

	highscoresText = sf::Text();
	highscoresText.setFont(generalFont);
	highscoresText.setCharacterSize(30.0);
	highscoresText.setFillColor(sf::Color(sf::Color::White));

	enterNickText = sf::Text();
	enterNickText.setString("Enter nickname:");
	enterNickText.setFont(generalFont);
	enterNickText.setCharacterSize(30.0);
	enterNickText.setFillColor(sf::Color(sf::Color::White));
	enterNickText.setPosition(0.0, 810.0);
	centerText(enterNickText);

	nick = "";
	nickText = sf::Text();
	nickText.setFont(generalFont);
	nickText.setCharacterSize(70.0);
	nickText.setFillColor(sf::Color(sf::Color::White));
	nickText.setPosition(0.0, 830.0);

	loadHighscores();

}

void gameover::run () {
	while(window.isOpen()) { // Main loop
		sf::Event event;

		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed)
				window.close();
			if(event.type == sf::Event::KeyReleased) {
				if(event.key.code == sf::Keyboard::Return) {
					if(!nick.empty()) {
						updateHighscores();
						saveHighscores();
						return;
					}
				}
			}
			if(event.type == sf::Event::KeyPressed) {
				editNick(event.key.code);
			}
		}
		window.clear();
		window.draw(gameOverText);
		window.draw(scoreText);
		drawHighscores();
		drawNick();
		window.display();
	}
}

void gameover::drawHighscores () {
	for(int i = 0; i < 10; i++) {
		std::string standing = std::to_string(i + 1) + ". ";
		std::string nick = std::get<std::string>(highscores.at(i));
		int result = std::get<int>(highscores.at(i));
		double yResultPos = 380.0 + 40.0 * i;

		highscoresText.setString(standing + nick);
		highscoresText.setPosition(420.0, yResultPos);
		window.draw(highscoresText);
		
		highscoresText.setString(std::to_string(result));
		highscoresText.setPosition(860.0, yResultPos);
		window.draw(highscoresText);
	}
}

void gameover::drawNick () {
	nickText.setString(nick);
	centerText(nickText);
	window.draw(enterNickText);
	window.draw(nickText);
}

void gameover::loadHighscores () {
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

		highscores.push_back(result);
	}
	highscoresFile.close();
}

void gameover::saveHighscores () {
	std::ofstream highscoresFile;
	highscoresFile.open("highscores.txt");
	if(!highscoresFile.is_open()) {
		throw std::ios_base::failure("Highscores file opening failed.");
	}

	for(std::pair<std::string, int> &result: highscores) {
		highscoresFile << 
		std::get<std::string>(result) << " " <<
		std::get<int>(result) << std::endl;
	}
	highscoresFile.close();
}

void gameover::updateHighscores () {
	std::pair<std::string, int> result (nick, score);

	for(uint i = 0; i < highscores.size(); i++) {
		if(score > std::get<int>(highscores[i])) {
			highscores.insert(highscores.begin() + i, result);
			highscores.pop_back();
			return;
		}
	}
}

void gameover::editNick (int keyCode) {
	char key = keyCode + 'a';

	if(isLetterAscii(key) && nick.length() < 16) {
		nick += key;
	}
	else if(keyCode == sf::Keyboard::BackSpace) {
		if(!nick.empty()) {
			nick.pop_back();
		}
	}
}

void gameover::centerText (sf::Text &text) {
	sf::FloatRect textRect = text.getGlobalBounds();
	double xTextPos = windowSize.x / 2 - textRect.width / 2;
	text.setPosition(xTextPos, text.getPosition().y);
}

bool gameover::isLetterAscii (char keyCode) {
	return (keyCode >= 'A' && keyCode <= 'Z') || (keyCode >= 'a' && keyCode <= 'z');
}
