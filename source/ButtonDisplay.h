#pragma once

#include "TextButton.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>


class ButtonDisplay
{
public:
	ButtonDisplay(sf::RenderWindow* windowPtr, sf::Font& bst, checkBox* detailBox, bool detailedBool, TextButton* tabSwitcher);
	void update();
	void draw();
	void resize();

	bool detailedActive = false;
	char currentTab = 1;

private:
	sf::RenderWindow* window;

	bool rmbBlock = true;

	bool hasFocus = true;

	sf::Vector2f spriteCenter = { 596 - 8, 356 - 8 };
	sf::Vector2i mouseLast = { 0,0 };
	bool mouseUpdate = false;
	char mouseUpdateFrames = 0;

	checkBox* detailed;
	TextButton* switchTabs;

	Label currentAPM;
	Label recentAPM;

	//Key MouseMovement;

	std::unique_ptr<checkBox> forward;
	std::unique_ptr<checkBox> back;
	std::unique_ptr<checkBox> left;
	std::unique_ptr<checkBox> right;

	std::unique_ptr<checkBox> jump;
	std::unique_ptr<checkBox> flip;

	std::unique_ptr<checkBox> attack;
	std::unique_ptr<checkBox> block;


	sf::Texture bigCircleText;
	sf::Texture smallCircleText;
	sf::Sprite bigCircle;
	sf::Sprite smallCircle;

};


