#include "main.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "TextButton.h"
#include <math.h>
#include <SFML/Audio.hpp>

const int mainWidth = 800;
const int mainHeight = 640;

int main()
{
	sf::RenderWindow mainWindow(sf::VideoMode(mainWidth, mainHeight), "Bobbys TBF Trainer");
	mainWindow.setFramerateLimit(250);

	sf::Font bst;
	bst.loadFromFile("bahnschrift.ttf");

	sf::SoundBuffer metronome;
	if (!metronome.loadFromFile("metronome.wav")) {
		std::cout << "failed to load sound";
		return -1;
	}
	sf::Sound sound;
	sound.setBuffer(metronome);


	sf::Clock fpsTimer;
	float fpsElapsed = 0;

	bool leftClickInit = false;
	bool rightClickInit = false;

	bool gender = true; //female is true, male is false


	bool slashActive = false;
	bool blockActive = false;
	bool failPossible = false;
	bool metronomeActive = false;

	int slashCounter = 0;
	int blockRelCounter = 0;
	int blockRecovery = 0;
	int failCounter = 0;
	int timeBetween = 0;
	int metronomeCounter = 0;

	int metronomeReset = 75;

	Label slashDown({ 240, 200 }, 24, "left click up", 4, bst);
	Label slashTimeL({ 260,220 }, 24, "0", 4, bst);
	Label blockDown({ 460, 200 }, 24, "right click up", 4, bst);
	Label blockTimeL({ 480, 220 }, 24, "0", 4, bst);
	Label FPSLabel({ 750, 10 }, 24, "FPS : ", 0, bst, { 50,0 });
	Label FPSCounter({ 750, 10 }, 24, "0", 4, bst);

	Label betweenLabel({ 400,300 }, 24, "Time between slash/block : ", 0, bst);
	Label timeBetweenSB({ 400,300 }, 24, "0", 4, bst);

	Label fastestPossLabel({ 400,400 }, 24, "Fastest possible TBF : ", 0, bst);
	Label fastestPossible({ 400, 400 }, 24, "0", 4, bst);

	//Textbox(sf::Vector2f pos, int fontSize, sf::Vector2f boxSize, sf::Color color, int limitInit, std::string string, bool isEditable)
	Textbox metronomeSpeed({ 300,80 }, 18, { 100,20 }, sf::Color::White, 3, "200", true);
	metronomeSpeed.setFont(bst);

	//checkBox(std::string string, sf::Vector2f pos, sf::Font& font) {
	checkBox metronomeCheck("metronome", { 300, 100 }, bst);


	Label SlashFailLabel({ 400, 140 }, 24, "slash : ", 0, bst);
	Label SlashFail({ 400, 140 }, 24, "fail", 4, bst);


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		slashDown.setText("left click down");
	}

	while (mainWindow.isOpen())
	{
		slashCounter += slashActive;
		blockRelCounter += sf::Mouse::isButtonPressed(sf::Mouse::Right) * blockActive;

		metronomeCounter++;
		if (metronomeCounter >= metronomeReset && metronomeCheck.getChecked()) {
			sound.play();
			metronomeCounter = 0;
		}

		FPSCounter.setText(std::to_string(static_cast<int>(round(1000000 / fpsTimer.restart().asMicroseconds()))));

		//SlashFail.setText(std::to_string(failPossible));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			
			slashDown.setText("left click down");
			
			if (!blockActive && !slashActive && !leftClickInit && !sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				slashActive = true;
				slashCounter = 0;
			}


			leftClickInit = true;
		}
		else {
			slashDown.setText("left click up");
			if (leftClickInit) {
				slashTimeL.setText(std::to_string(slashCounter));
			}
			leftClickInit = slashActive;
			if (slashCounter > 145) {
				slashActive = false;
			}
		}
		

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			blockDown.setText("right click down");

			if (!blockActive && !rightClickInit) {
				blockRecovery = 0;
				blockRelCounter = 0;
				blockActive = true;
				if (!slashActive) {
					SlashFail.setText("fail");
					SlashFail.setTextColor(sf::Color::Red);
				}
				else {
					timeBetweenSB.setText(std::to_string(slashCounter));
					SlashFail.setText("pass");
					SlashFail.setTextColor(sf::Color::Black);
				}

				slashActive = false;
			}
			
			rightClickInit = true;
		}
		else {
			if (rightClickInit && blockActive) {
				blockTimeL.setText(std::to_string(blockRelCounter));
			}
			
			blockDown.setText("right click up");
			blockRecovery += blockActive;
			blockActive = blockRecovery < 60;
			if (blockRecovery >= 60) {
				blockActive = false;
				rightClickInit = false;
			}
		}



		sf::Event event;
		while (mainWindow.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed: {
				mainWindow.close();
				break;
			}

			
			case sf::Event::MouseButtonPressed: {
				if (event.mouseButton.button == sf::Mouse::Left) {
					metronomeCheck.isMouseOver(mainWindow);
					if (metronomeCheck.getChecked()) {
						metronomeReset = 60 * 250 / stoi(metronomeSpeed.getText());
					}

					//metronomeSpeed.setActivity(metronomeSpeed.isMouseOver(mainWindow));
					metronomeSpeed.isMouseOver(mainWindow);

				}
				break;
			}
			case sf::Event::TextEntered: {
				metronomeSpeed.typedOn(event);
			}
			/*
			case sf::Event::MouseButtonReleased: {
				if (event.mouseButton.button == sf::Mouse::Left) {
					leftClickDown = false;
					slashDown.setText("left click up");
					//slashTimeL.setText(std::to_string(static_cast<int>(round(1000000 / slashTimer.restart().asMicroseconds()))));
					slashTimeL.setText(std::to_string(slashCounter));

					
				}
				if (event.mouseButton.button == sf::Mouse::Right) {
					rightClickDown = false;
					failCounter = 0;
					failPossible = true;
					blockDown.setText("right click up");
					//blockTimeL.setText(std::to_string(static_cast<int>(round(1000000 / blockTimer.restart().asMicroseconds()))));
					blockTimeL.setText(std::to_string(blockCounter));
					fastestPossible.setText(std::to_string(250 * 60 / (blockCounter + timeBetween + 60)));
				}
				break;
			}
			*/
			default: {
				break;
			}
			}
		}
		mainWindow.clear(sf::Color::White);

		//slashPMButt.draw(mainWindow);

		slashDown.drawTo(mainWindow);
		slashTimeL.drawTo(mainWindow);
		blockDown.drawTo(mainWindow);
		blockTimeL.drawTo(mainWindow);

		FPSLabel.drawTo(mainWindow);
		FPSCounter.drawTo(mainWindow);


		timeBetweenSB.drawTo(mainWindow);
		betweenLabel.drawTo(mainWindow);

		fastestPossible.drawTo(mainWindow);
		fastestPossLabel.drawTo(mainWindow);

		SlashFail.drawTo(mainWindow);
		SlashFailLabel.drawTo(mainWindow);

		metronomeSpeed.drawTo(mainWindow);
		metronomeCheck.draw(mainWindow);

		mainWindow.display();

	}

	

	return 0;

}