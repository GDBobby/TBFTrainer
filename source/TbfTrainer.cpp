#include "tbfTrainer.h"

#include <iostream>


TbfTrainer::TbfTrainer(sf::RenderWindow* windowPtr, sf::Font& bst, checkBox* detailBox, bool detailedBool, TextButton* tabSwitcher) {
	window = windowPtr;

	//sf::Font bst = font;

	
	if (!metronome.loadFromFile("metronome.wav")) {
		std::cout << "failed to load sound";
		window->close();
	}
	sound.setBuffer(metronome);

	detailed = detailBox;
	detailedActive = detailedBool;
	switchTabs = tabSwitcher;

	//Label(sf::Vector2f pos, int fontSz, std::string string, char relation, sf::Font& font, sf::Vector2f relationSize);
	sf::Vector2f position = { mainWidth - 50, 180 };
	sf::Vector2f relPos = { 0,0 };
	slashDown = std::make_unique<Label>(position, 24, "left click up", 0, bst);

	position = { mainWidth - 50, 180 };
	slashTimeL = std::make_unique<Label>(position, 24, "0", 4, bst);
	position = { mainWidth - 50, 200 };
	blockDown = std::make_unique<Label>(position, 24, "right click up", 0, bst);
	blockTimeL = std::make_unique<Label>(position, 24, "0", 4, bst);

	position = {mainWidth - 50, 260};
	relPos = { 20,0 };
	jumpReset = std::make_unique<checkBox>("instant jump reset", position, bst, 0);
	position = { mainWidth - 50, 280 };
	jumpSlashLabel = std::make_unique<Label>(position, 24, "Time between jump/slash : ", 0, bst);
	jumpSlash = std::make_unique<Label>(position, 24, "0", 4, bst);

	position = { mainWidth - 50, 300 };
	betweenLabel = std::make_unique<Label>(position, 24, "Time between slash/block : ", 0, bst);
	timeBetweenSB = std::make_unique<Label>(position, 24, "0", 4, bst);

	position = { mainWidth - 50, 400 };
	currentSpeedLabel = std::make_unique<Label>(position, 24, "Current Speed : ", 0, bst);
	currentSpeed = std::make_unique<Label>(position, 24, "0", 4, bst);

	position = { mainWidth - 50, 340 };
	timeIdleSlashLabel = std::make_unique<Label>(position, 24, "Time between block drop and slash : ", 0, bst);
	timeIdleSlash = std::make_unique<Label>(position, 24, "0", 4, bst);

	position = { mainWidth - 50, 75 };
	sf::Vector2f boxSize = { 40,20 };
	metronomeSpeed = std::make_unique<Textbox>(position, 18, bst, boxSize, sf::Color::White, 3, "200");

	position = { mainWidth - 110, 95 };
	sf::Vector2f tempRel = { 15,0 };
	metronomeCheck = std::make_unique<checkBox>("metronome", position, bst, 2, tempRel);

	position = { mainWidth - 60, 140 };
	SlashFailLabel = std::make_unique<Label>(position, 24, "slash : ", 0, bst);
	SlashFail = std::make_unique<Label>(position, 24, "fail", 4, bst);

	position = { mainWidth - 50, 420 };
	AverageLabel = std::make_unique<Label>(position, 24, "Average Speed : ", 0, bst);
	AverageSpeed = std::make_unique<Label>(position, 24, "0", 4, bst);
}

void TbfTrainer::resize() {
	window->setSize({ 400, 500 });
	sf::FloatRect visibleArea(0.f, 0.f, 400.f, 500.f);
	window->setView(sf::View(visibleArea));
}

void TbfTrainer::update() {

	//SlashFail.setText(std::to_string(failPossible));

	idleCounter += idleActive;
	slashCounter += slashActive;
	blockRelCounter += sf::Mouse::isButtonPressed(sf::Mouse::Right) * blockActive;
	jumpCounter += jumpActive;

	metronomeCounter++;
	if ((metronomeCounter >= metronomeReset) && metronomeCheck->getChecked()) {
		//std::cout << "sound play" << std::endl;
		sound.play();
		metronomeCounter = 0;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

		slashDown->setText("left click down");

		if (!blockActive && !slashActive && !leftClickInit && !sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			slashActive = true;
			slashCounter = 0;

			if (instantJumpReset && jumpActive) {
				jumpSlash->setText(std::to_string(jumpCounter));
				//std::cout << "why here" << std::endl;
				jumpActive = false;
			}
			else if (jumpActive) {
				jumpSlash->setText(std::to_string(jumpCounter));
			}
			if (idleActive) {
				idleActive = false;
				timeIdleSlash->setText(std::to_string(idleCounter));
				timeIdleSlash->setTextColor(sf::Color::Black);
			}
		}
		else if (blockActive && !leftClickInit) {
			timeIdleSlash->setText(std::to_string(blockRecovery));
			timeIdleSlash->setTextColor(sf::Color::Red);
		}

		leftClickInit = true;
	}
	else {
		slashDown->setText("left click up");
		if (leftClickInit) {
			slashTimeL->setText(std::to_string(slashCounter));
		}
		leftClickInit = slashActive;
		if (slashCounter > 145) {
			slashActive = false;
		}
	}


	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		blockDown->setText("right click down");

		if (!blockActive && !rightClickInit) {
			blockRecovery = 0;
			blockRelCounter = 0;
			blockActive = true;
			if (!slashActive) {
				SlashFail->setText("fail");
				SlashFail->setTextColor(sf::Color::Red);
			}
			else {
				timeBetweenSB->setText(std::to_string(slashCounter));
				SlashFail->setText("pass");
				SlashFail->setTextColor(sf::Color::Black);
			}

			slashActive = false;
		}

		rightClickInit = true;
	}
	else {
		if (rightClickInit && blockActive) {
			blockTimeL->setText(std::to_string(blockRelCounter));
		}

		blockDown->setText("right click up");
		blockRecovery += blockActive;
		if (blockRecovery >= 60) {

			currentSpeed->setText(std::to_string((250 * 60) / (idleCounter + slashCounter + blockRelCounter + 59 + gender)));
			averageCounter++;
			averageSpeed += (250 * 60) / (idleCounter + slashCounter + blockRelCounter + 59 + gender);
			//averageSpeed = ((averageSpeed * averageCounter - 1) + (250 * 60) / (idleCounter + slashCounter + blockRelCounter + 59 + gender)) / averageCounter;
			AverageSpeed->setText(std::to_string(averageSpeed / averageCounter));
			blockRecovery = 0;
			blockActive = false;
			rightClickInit = false;
			idleActive = true;
			idleCounter = 0;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !jumpInit) {
		jumpInit = true;
		jumpActive = true;
		jumpCounter = 0;
	}
	else if (jumpCounter >= 185 || (!jumpActive && instantJumpReset && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))) {
		jumpInit = false;
	}


	sf::Event event;
	while (window->pollEvent(event))
	{
		switch (event.type) {
		case sf::Event::Closed: {
			window->close();
			break;
		}


		case sf::Event::MouseButtonPressed: {
			if (event.mouseButton.button == sf::Mouse::Left) {
				metronomeCheck->isMouseOver(*window);
				if (metronomeCheck->getChecked()) {
					metronomeReset = 60 * 250 / stoi(metronomeSpeed->getText());
					std::cout << "reset speed : text : " << metronomeReset << ":" << stoi(metronomeSpeed->getText()) << std::endl;
				}
				jumpReset->isMouseOver(*window);
				instantJumpReset = jumpReset->getChecked();

				detailed->isMouseOver(*window);
				if (detailedActive != detailed->getChecked()) {
					detailedActive = !detailedActive;
				}
				if (switchTabs->isMouseOver(*window)) {
					currentTab = 1;
				}


				//metronomeSpeed.setActivity(metronomeSpeed.isMouseOver(mainWindow));
				metronomeSpeed->isMouseOver(*window);

			}
			break;
		}
		case sf::Event::TextEntered: {
			metronomeSpeed->typedOn(event);
		}
		default: {
			break;
		}
		}
	}

}

void TbfTrainer::draw() {
	slashDown->drawTo(*window);
	slashTimeL->drawTo(*window);
	blockDown->drawTo(*window);
	blockTimeL->drawTo(*window);

	timeBetweenSB->drawTo(*window);
	betweenLabel->drawTo(*window);

	currentSpeedLabel->drawTo(*window);
	currentSpeed->drawTo(*window);

	AverageLabel->drawTo(*window);
	AverageSpeed->drawTo(*window);

	SlashFail->drawTo(*window);
	SlashFailLabel->drawTo(*window);

	timeIdleSlash->drawTo(*window);
	timeIdleSlashLabel->drawTo(*window);

	metronomeSpeed->drawTo(*window);
	metronomeCheck->draw(*window);

	jumpSlash->drawTo(*window);
	jumpSlashLabel->drawTo(*window);
	jumpReset->draw(*window);
}
