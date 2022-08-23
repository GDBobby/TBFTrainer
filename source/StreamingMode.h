#pragma once
#include "TextButton.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>


class StreamingMode
{
public:
	StreamingMode(sf::RenderWindow* windowPtr, sf::Font& bst, checkBox* detailBox, bool detailedBool, TextButton* tabSwitcher);
	sf::RenderWindow* window;

	void update();
	void draw();
	void resize();

	bool detailedActive;
	char currentTab = 2;

private:
	TextButton* switchTabs;
	checkBox* detailed;

	int currentFrame = 0;
	unsigned char heroScore = 0;
	unsigned char villainScore = 0;

	std::unique_ptr<Textbox> hero;
	std::unique_ptr<Textbox> villain;
	std::unique_ptr<Label> heroScoreDisplay;
	std::unique_ptr<Label> villainScoreDisplay;

	bool heroIncreaseDown = false;
	bool heroDecreaseDown = false;
	
	bool villainIncreaseDown = false;
	bool villainDecreaseDown = false;


};

