#include "main.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "TextButton.h"
#include <math.h>
#include <SFML/Audio.hpp>
#include <chrono>

const int mainWidth = 400;
const int mainHeight = 500;
#define LOGIC_TIME .004f

int WinMain()
{
	sf::RenderWindow mainWindow(sf::VideoMode(mainWidth, mainHeight), "Bobbys TBF Trainer");
	//mainWindow.setFramerateLimit(250);

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

	bool jumpActive = false;
	bool slashActive = false;
	bool blockActive = false;
	//bool failPossible = false;
	bool metronomeActive = false;
	bool idleActive = false;
	bool jumpInit = false;

	bool instantJumpReset = false;

	int slashCounter = 0;
	int blockRelCounter = 0;
	int blockRecovery = 0;
	//int failCounter = 0;
	int timeBetween = 0;
	int idleCounter = 0;

	float logicTime = 0.0f;

	int averageCounter = 0;
	int averageSpeed = 0;

	int jumpCounter = 0;

	int metronomeCounter = 0;

	int metronomeReset = 75;

	Label slashDown({ mainWidth - 50, 180 }, 24, "left click up", 0, bst);
	Label slashTimeL({ mainWidth - 50,180 }, 24, "0", 4, bst);
	Label blockDown({ mainWidth - 50, 200 }, 24, "right click up", 0, bst);
	Label blockTimeL({ mainWidth - 50, 200 }, 24, "0", 4, bst);



	Label FPSLabel({ mainWidth - 50, 0}, 24, "FPS : ", 0, bst, { 50,0 });
	Label FPSCounter({ mainWidth - 50, 0}, 24, "0", 4, bst);


	checkBox jumpReset("instant jump reset", { mainWidth - 50, 260}, bst);
	jumpReset.setPosition({ mainWidth - 50, 260 }, 0);
	Label jumpSlashLabel({ mainWidth - 50,280 }, 24, "Time between jump/slash : ", 0, bst);
	Label jumpSlash({ mainWidth - 50,280 }, 24, "0", 4, bst);

	Label betweenLabel({ mainWidth - 50,300 }, 24, "Time between slash/block : ", 0, bst);
	Label timeBetweenSB({ mainWidth - 50,300 }, 24, "0", 4, bst);

	Label currentSpeedLabel({ mainWidth - 50,400 }, 24, "Current Speed : ", 0, bst);
	Label currentSpeed({ mainWidth - 50, 400 }, 24, "0", 4, bst);

	Label timeIdleSlashLabel({ mainWidth - 50,340 }, 24, "Time between block drop and slash : ", 0, bst);
	Label timeIdleSlash({ mainWidth - 50,340 }, 24, "0", 4, bst);

	Textbox metronomeSpeed({ mainWidth - 50,80 }, 18, { 40,20 }, sf::Color::White, 3, "200", true);
	metronomeSpeed.setFont(bst);
	checkBox metronomeCheck("metronome", { mainWidth - 50, 100 }, bst);
	metronomeCheck.setPosition({ mainWidth - 50,95 }, 0);


	Label SlashFailLabel({ mainWidth - 60, 140 }, 24, "slash : ", 0, bst);
	Label SlashFail({ mainWidth - 60, 140 }, 24, "fail", 4, bst);

	Label AverageLabel({ mainWidth - 50,420 }, 24, "Average Speed : ", 0, bst);
	Label AverageSpeed({ mainWidth - 50, 420 }, 24, "0", 4, bst);


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		slashDown.setText("left click down");
	}

	auto currentTime = std::chrono::high_resolution_clock::now();

	while (mainWindow.isOpen())
	{
		auto newTime = std::chrono::high_resolution_clock::now();
		auto timeDiff = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
		logicTime += timeDiff;

		currentTime = newTime;

		if (logicTime >= LOGIC_TIME) {
			//std::cout << "logic loop : " << logicTime << std::endl;
			logicTime -= LOGIC_TIME;

			idleCounter += idleActive;
			slashCounter += slashActive;
			blockRelCounter += sf::Mouse::isButtonPressed(sf::Mouse::Right) * blockActive;
			jumpCounter += jumpActive;
			//if (jumpInit) { std::cout << "jumpcounter after:jumpreset:jumpinit:jumpActive : " << jumpCounter << ":" << instantJumpReset << ":" << jumpInit << ":" << jumpActive << std::endl; }

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

					if (instantJumpReset && jumpActive) {
						jumpSlash.setText(std::to_string(jumpCounter));
						//std::cout << "why here" << std::endl;
						jumpActive = false;
					}
					else if (jumpActive) {
						jumpSlash.setText(std::to_string(jumpCounter));
					}
					if (idleActive) {
						idleActive = false;
						timeIdleSlash.setText(std::to_string(idleCounter));
						timeIdleSlash.setTextColor(sf::Color::Black);
					}
				}
				else if (blockActive && !leftClickInit) {
					timeIdleSlash.setText(std::to_string(blockRecovery));
					timeIdleSlash.setTextColor(sf::Color::Red);
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
				if (blockRecovery >= 60) {

					currentSpeed.setText(std::to_string((250 * 60) / (idleCounter + slashCounter + blockRelCounter + 59 + gender)));
					averageCounter++;
					averageSpeed += (250 * 60) / (idleCounter + slashCounter + blockRelCounter + 59 + gender);
					//averageSpeed = ((averageSpeed * averageCounter - 1) + (250 * 60) / (idleCounter + slashCounter + blockRelCounter + 59 + gender)) / averageCounter;
					AverageSpeed.setText(std::to_string(averageSpeed / averageCounter));
					blockRecovery = 0;
					blockActive = false;
					rightClickInit = false;
					idleActive = true;
					idleCounter = 0;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !jumpInit) {
				std::cout << "entered jump activation" << std::endl;
				jumpInit = true;
				jumpActive = true;
				jumpCounter = 0;
			}
			else if (jumpCounter >= 185 || (!jumpActive && instantJumpReset && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))) {
				jumpInit = false;
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
						jumpReset.isMouseOver(mainWindow);
						instantJumpReset = jumpReset.getChecked();

						//metronomeSpeed.setActivity(metronomeSpeed.isMouseOver(mainWindow));
						metronomeSpeed.isMouseOver(mainWindow);

					}
					break;
				}
				case sf::Event::TextEntered: {
					metronomeSpeed.typedOn(event);
				}
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

			currentSpeedLabel.drawTo(mainWindow);
			currentSpeed.drawTo(mainWindow);

			AverageLabel.drawTo(mainWindow);
			AverageSpeed.drawTo(mainWindow);

			SlashFail.drawTo(mainWindow);
			SlashFailLabel.drawTo(mainWindow);

			timeIdleSlash.drawTo(mainWindow);
			timeIdleSlashLabel.drawTo(mainWindow);

			metronomeSpeed.drawTo(mainWindow);
			metronomeCheck.draw(mainWindow);

			jumpSlash.drawTo(mainWindow);
			jumpSlashLabel.drawTo(mainWindow);
			jumpReset.draw(mainWindow);

			mainWindow.display();

		}


	}
	return 0;

}