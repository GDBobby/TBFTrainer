#include "StreamingMode.h"


StreamingMode::StreamingMode(sf::RenderWindow* windowPtr, sf::Font& bst, checkBox* detailBox, bool detailedBool, TextButton* tabSwitcher) {
	window = windowPtr;
	detailed = detailBox;
	detailedActive = detailedBool;
	switchTabs = tabSwitcher;

									//(sf::Vector2f pos, int fontSize, sf::Font& font, std::string labstring, std::string boxstring, sf::Vector2f boxSize, sf::Color color, int limitInit, char relation)
	sf::Vector2f tempPos = { 0, 60 };
	sf::Vector2f boxSize = { 200,60 };
	sf::Vector2f tempRel = { 0,70 };
	hero = std::make_unique<Textbox>(tempPos, 48, bst, boxSize, sf::Color::White, 100, "hero");


	tempPos = {200, 40};
	heroScoreDisplay = std::make_unique<Label>(tempPos, 64, "0", 0, bst, tempRel);


	tempPos = { 740, 40 };
	villainScoreDisplay = std::make_unique<Label>(tempPos, 64, "0", 0, bst, tempRel);
											//(position, 18, bst, boxSize, sf::Color::White, 3, "200");
	tempPos = { 800,60 };
	villain = std::make_unique<Textbox>(tempPos, 48, bst, boxSize, sf::Color::White, 100, "villain");
	
	hero->setTextColor({ 0,128,0,255 });
	heroScoreDisplay->setTextColor({ 0,128,0,255 });

	villain->setTextColor({ 0,128,0,255 });
	villainScoreDisplay->setTextColor({ 0,128,0,255 });

	hero->setBoxTrans();
	villain->setBoxTrans();

	hero->numberOnly = false;
	villain->numberOnly = false;
}

void StreamingMode::update() {

	/*
	if (event.key.code == sf::Keyboard::J) {
		heroScore++;
		heroScoreDisplay->setText(std::to_string(heroScore));
		std::cout << "hero plus" << std::endl;
	}
	if (event.key.code == sf::Keyboard::K) {
		villainScore++;
		villainScoreDisplay->setText(std::to_string(villainScore));
	}
	if (event.key.code == sf::Keyboard::N) {
		heroScore--;
		heroScoreDisplay->setText(std::to_string(heroScore));
	}
	if (event.key.code == sf::Keyboard::M) {
		villainScore--;
		villainScoreDisplay->setText(std::to_string(villainScore));
	}
	*/
	if (!heroIncreaseDown && sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
		heroIncreaseDown = true;
		heroScore++;
		heroScoreDisplay->setText(std::to_string(heroScore));
	}
	else if (heroIncreaseDown && !sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
		heroIncreaseDown = false;
	}

	if (!heroDecreaseDown && sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
		heroDecreaseDown = true;
		heroScore--;
		heroScoreDisplay->setText(std::to_string(heroScore));
	}
	else if (heroDecreaseDown && !sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
		heroDecreaseDown = false;
	}	

	if (!villainIncreaseDown && sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
		villainIncreaseDown = true;
		villainScore++;
		villainScoreDisplay->setText(std::to_string(villainScore));
	}
	else if (villainIncreaseDown && !sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
		villainIncreaseDown = false;
	}	

	if (!villainDecreaseDown && sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
		villainDecreaseDown = true;
		villainScore--;
		villainScoreDisplay->setText(std::to_string(villainScore));
	}
	else if (villainDecreaseDown && !sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
		villainDecreaseDown = false;
	}

	sf::Event event;
	while (window->pollEvent(event))
	{
		switch (event.type) {
		case sf::Event::Closed: {
			window->close();
			break;
		}
		case sf::Event::KeyPressed: {
			if (event.key.code == sf::Keyboard::F12) {
				currentTab = 0;
			}
		}

		case sf::Event::MouseButtonPressed: {
			if (event.mouseButton.button == sf::Mouse::Left) {

				hero->isMouseOver(*window);
				
				villain->isMouseOver(*window);

			}
			break;
		}
		case sf::Event::TextEntered: {
			hero->typedOn(event);
			villain->typedOn(event);
		}
		default: {
			break;
		}
		}
	}
}

void StreamingMode::draw() {
	hero->drawTo(*window);
	villain->drawTo(*window);
	heroScoreDisplay->drawTo(*window);
	villainScoreDisplay->drawTo(*window);
}

void StreamingMode::resize() {
	window->setSize({ 1000, 400 });
	sf::FloatRect visibleArea(0.f, 0.f, 1000.f, 400.f);
	window->setView(sf::View(visibleArea));
}