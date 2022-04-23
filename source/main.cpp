#include "main.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "TextButton.h"
#include <math.h>

const int mainWidth = 800;
const int mainHeight = 640;

int main()
{
	sf::RenderWindow mainWindow(sf::VideoMode(mainWidth, mainHeight), "Bobbys TBF Trainer");
	mainWindow.setFramerateLimit(250);
	sf::Font bst;
	bst.loadFromFile("bahnschrift.ttf");


	sf::Clock fpsTimer;
	float fpsElapsed = 0;

	bool leftClickDown = false;
	bool rightClickDown = false;

	sf::Clock slashTimer;
	sf::Clock blockTimer;
	int slashCounter = 0;
	int blockCounter = 0;

	//TextButton(std::string t, sf::Vector2f pos, int charSize, sf::Color bgColor, sf::Color tColor, sf::Font& font, float butSz)
	TextButton slashPMButt("BF here", { 200,300 }, 24, sf::Color::Green, sf::Color::Red, bst, 20);
	slashPMButt.setPosition({340,300});

	//Label(sf::Vector2f pos, int fontSz, std::string string, char relation, sf::Font& font, sf::Vector2f relationSize = { 100,0 })
	Label slashDown({240, 200}, 24, "left click up", 4, bst);
	Label slashTimeL({ 260,220 }, 24, "0", 4, bst);
	Label blockDown({ 460, 200 }, 24, "right click up", 4, bst);
	Label blockTimeL({ 480, 220 }, 24, "0", 4, bst);
	Label FPSLabel({ 750, 10 }, 24, "FPS : ", 0, bst, { 50,0 });
	Label FPSCounter({ 750, 10 }, 24, "0", 4, bst);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		slashDown.setText("left click down");
	}

	while (mainWindow.isOpen())
	{
		//fpsElapsed = fpsTimer.restart().asMicroseconds();

		FPSCounter.setText(std::to_string(static_cast<int>(round(1000000 / fpsTimer.restart().asMicroseconds()))));
		slashCounter += leftClickDown;
		blockCounter += rightClickDown;

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
					slashPMButt.isMouseOver(mainWindow);
					leftClickDown = true;
					slashDown.setText("left click down");
					slashTimer.restart();
					slashCounter = 0;
				}
				if (event.mouseButton.button == sf::Mouse::Right) {
					rightClickDown = true;
					slashPMButt.isMouseOver(mainWindow);
					blockTimer.restart();
					blockDown.setText("right click down");
				}
				break;
			}
			case sf::Event::MouseButtonReleased: {
				if (event.mouseButton.button == sf::Mouse::Left) {
					leftClickDown = false;
					slashDown.setText("left click up");
					//slashTimeL.setText(std::to_string(static_cast<int>(round(1000000 / slashTimer.restart().asMicroseconds()))));
					slashTimeL.setText(std::to_string(slashCounter));

					
				}
				if (event.mouseButton.button == sf::Mouse::Right) {
					rightClickDown = false;
					blockDown.setText("right click up");
					blockTimeL.setText(std::to_string(static_cast<int>(round(1000000 / blockTimer.restart().asMicroseconds()))));
				}
				break;
			}
			default: {
				break;
			}
			}
		}
		mainWindow.clear(sf::Color::White);

		slashPMButt.draw(mainWindow);

		slashDown.drawTo(mainWindow);
		slashTimeL.drawTo(mainWindow);
		blockDown.drawTo(mainWindow);
		blockTimeL.drawTo(mainWindow);

		FPSLabel.drawTo(mainWindow);
		FPSCounter.drawTo(mainWindow);

		mainWindow.display();

	}

	

	return 0;

}