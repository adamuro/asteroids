#include "menu.hpp"

menu::menu (sf::RenderWindow &window_): 
	windowSize(window_.getSize()),
	window(window_) {
	asteroidsFont = sf::Font();
	asteroidsFont.loadFromFile("./fonts/Starjedi.ttf");
	asteroidsText = sf::Text();
	asteroidsText.setString("Asteroids");
	asteroidsText.setFont(asteroidsFont);
	asteroidsText.setCharacterSize(150.0);
	asteroidsText.setFillColor(sf::Color(sf::Color::White));
	asteroidsText.setPosition(0.0, 100.0);
	centerText(asteroidsText);

	optionsFont = sf::Font();
	optionsFont.loadFromFile("./fonts/BebasNeue-Regular.ttf");

	optionsString[play] = "Play";
	optionsString[highscores] = "Highscores";
	optionsString[exit] = "Exit";

	for(sf::Text &option: optionsText) {
		option = sf::Text();
		option.setFont(optionsFont);
		option.setCharacterSize(50.0);
		option.setFillColor(sf::Color(sf::Color::White));
	}

	for(int i = 0; i < 3; i++) {
		optionsText[i].setString(optionsString[i]);
		optionsText[i].setPosition(0.0, 400.0 + i * 100.0);
		centerText(optionsText[i]);
	}
	choice = play;
}

int menu::run () {
	while(window.isOpen()) { // Main loop
		sf::Event event;

		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed)
				window.close();
			if(event.type == sf::Event::KeyReleased) {
				if(event.key.code == sf::Keyboard::Up) {
					choice--;
					if(choice < play)
						choice = exit;
				}
				if(event.key.code == sf::Keyboard::Down) {
					choice++;
					if(choice > exit)
						choice = play;
				}
				if(event.key.code == sf::Keyboard::Return) {
					return choice;
				}
			}
		}
		window.clear();
		window.draw(asteroidsText);
		drawOptions();
		window.display();
	}
	return -1; // Error
}

void menu::drawOptions () {
	optionsText[choice].setStyle(sf::Text::Style::Underlined);
	for(sf::Text &option: optionsText) {
		centerText(option);
		window.draw(option);
		option.setStyle(sf::Text::Style::Regular);
	}
}

void menu::centerText (sf::Text &text) {
	sf::FloatRect textRect = text.getGlobalBounds();
	double xTextPos = windowSize.x / 2 - textRect.width / 2;
	text.setPosition(xTextPos, text.getPosition().y);
}