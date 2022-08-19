#include "main.h"

//SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

//SFML extension (mine)
#include "TextButton.h"

//program files
#include "TbfTrainer.h"
#include "ButtonDisplay.h"

//std
#include <math.h>
#include <chrono>
#include <format>



const int mainWidth = 400;
const int mainHeight = 500;
#define LOGIC_TIME .004f

// main() for DEBUG mode
// WinMain() for RELEASE mode

int WinMain()
{
	sf::RenderWindow mainWindow(sf::VideoMode(mainWidth, mainHeight), "Bobbys TBF Trainer");
	//mainWindow.setFramerateLimit(250);

	sf::Font bst;
	bst.loadFromFile("bahnschrift.ttf");



	sf::Clock fpsTimer;
	float fpsElapsed = 0;

	bool gender = true; //female is true, male is false

	bool detailedActive = false;

	float logicTime = 0.0f;

	int averageCounter = 0;
	int averageSpeed = 0;

	//Label(sf::Vector2f pos, int fontSz, std::string string, char relation, sf::Font& font, sf::Vector2f relationSize);

	sf::Vector2f tempPos = { mainWidth - 50, 0 };
	sf::Vector2f tempRel = { 50,0 };
	Label FPSLabel(tempPos, 24, "FPS : ", 0, bst, tempRel);
	Label FPSCounter(tempPos, 24, "0", 4, bst, tempRel);

	tempPos = { 0,0 };
	tempRel = { 0,0 };
	Label averageFrameLabel(tempPos, 24, "Average Frame : ", 4, bst, tempPos);
	tempPos = { 0, 24 };
	Label peakFrameLabel(tempPos, 24, "Peak Frame : ", 4, bst, tempRel);
	tempPos = { 0,48 };
	Label minFrameLabel(tempPos, 24, "Min Frame : ", 4, bst, tempRel);
	tempPos = { 0,72 };
	Label currentFrameLabel(tempPos, 24, "Min Frame : ", 4, bst, tempRel);


	//checkBox(std::string string, sf::Vector2f pos, sf::Font& font, char relation, sf::Vector2f posDif);
	tempPos = { mainWidth - 80,25 };
	tempRel = { 20,0 };
	checkBox detailed("Details", tempPos, bst, 2, tempRel);

	char currentTab = 0;

	TextButton switchTabs("Switch Tabs", { 5,100 }, 24, sf::Color::Black, sf::Color::Red, bst, 2);

	/*
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		slashDown.setText("left click down");
	}
	*/

	auto currentTime = std::chrono::high_resolution_clock::now();
	float totalFrameTime = 0.0f;
	float averageFrameTime = 0.0f;
	int framesCounted = 0;
	float peakFrameTime = 0.0f;
	float minFrameTime = 1.0f;

	//(sf::RenderWindow *windowPtr, sf::Font &bst, checkBox *detailBox, bool *detailedBool, TextButton *tabSwitcher, char *tabChar);
	TbfTrainer tbfTrainer(&mainWindow, bst, &detailed, detailedActive, &switchTabs);
	ButtonDisplay buttonDisplay(&mainWindow, bst, &detailed, detailedActive, &switchTabs);

	while (mainWindow.isOpen())
	{
		auto newTime = std::chrono::high_resolution_clock::now();
		auto timeDiff = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
		logicTime += timeDiff;

		currentTime = newTime;

		if (logicTime >= LOGIC_TIME) {
			//std::cout << "logic loop : " << logicTime << std::endl;
			if ((framesCounted % 2500) == 0) {
				totalFrameTime = 0;
				framesCounted = 0;
				peakFrameTime = 0;
				minFrameTime = 1.0f;
			}

			totalFrameTime += logicTime;
			framesCounted++;
			averageFrameTime = totalFrameTime / framesCounted;
			if (logicTime > peakFrameTime) {
				peakFrameTime = logicTime;
			}
			if (logicTime < minFrameTime) {
				minFrameTime = logicTime;
			}

			std::string bufferString = "Average Frame : " + std::format("{:.4f}", averageFrameTime);
			averageFrameLabel.setText(bufferString);
			bufferString = "Peak Frame : " + std::format("{:.4f}", peakFrameTime);
			peakFrameLabel.setText(bufferString);
			bufferString = "Min Frame : " + std::format("{:.4f}", minFrameTime);
			minFrameLabel.setText(bufferString);
			bufferString = "Current Frame : " + std::format("{:.4f}", logicTime);
			currentFrameLabel.setText(bufferString);

			logicTime -= LOGIC_TIME;

	
			//if (jumpInit) { std::cout << "jumpcounter after:jumpreset:jumpinit:jumpActive : " << jumpCounter << ":" << instantJumpReset << ":" << jumpInit << ":" << jumpActive << std::endl; }


			//std::cout << "currentTab : " << +currentTab << std::endl;
			FPSCounter.setText(std::to_string(static_cast<int>(round(1000000 / fpsTimer.restart().asMicroseconds()))));
			if (currentTab == 0) {
				tbfTrainer.update();

				detailedActive = tbfTrainer.detailedActive;
				buttonDisplay.detailedActive = detailedActive;
				
				if (tbfTrainer.currentTab != currentTab) {
					currentTab = tbfTrainer.currentTab;
					buttonDisplay.currentTab = currentTab;
					buttonDisplay.resize();
				}

				mainWindow.clear(sf::Color::White);

				tbfTrainer.draw();

				switchTabs.draw(mainWindow); 
				detailed.draw(mainWindow);

				if (detailedActive) {
					averageFrameLabel.drawTo(mainWindow);
					peakFrameLabel.drawTo(mainWindow);
					minFrameLabel.drawTo(mainWindow);
					currentFrameLabel.drawTo(mainWindow);
					FPSLabel.drawTo(mainWindow);
					FPSCounter.drawTo(mainWindow);
				}

				mainWindow.display();

			}
			if (currentTab == 1) {

				buttonDisplay.update();

				detailedActive = buttonDisplay.detailedActive;
				tbfTrainer.detailedActive = detailedActive;

				if (buttonDisplay.currentTab != currentTab) {
					currentTab = buttonDisplay.currentTab;
					tbfTrainer.currentTab = currentTab;
					tbfTrainer.resize();
				}

				mainWindow.clear(sf::Color::White);

				buttonDisplay.draw();
				
				switchTabs.draw(mainWindow);
				detailed.draw(mainWindow);

				if (detailedActive) {
					averageFrameLabel.drawTo(mainWindow);
					peakFrameLabel.drawTo(mainWindow);
					minFrameLabel.drawTo(mainWindow);
					currentFrameLabel.drawTo(mainWindow);
					FPSLabel.drawTo(mainWindow);
					FPSCounter.drawTo(mainWindow);
				}


				mainWindow.display();
			}
		
		}


	}
	return 0;

}