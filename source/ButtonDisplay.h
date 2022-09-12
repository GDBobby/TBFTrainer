#pragma once

#include "TextButton.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>


#define ARRAYSIZE 7500

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

	bool hasFocus = true;

	sf::Vector2f spriteCenter = { 596 - 8, 356 - 8 };
	sf::Vector2i mouseLast = { 0,0 };
	bool mouseUpdate = false;
	char mouseUpdateFrames = 0;

	char apmArray[ARRAYSIZE];
	int totalButtonsPressed = 0;
	int recentButtonsPressed = 0;
	int totalButtonFrames = 0;
	int currentButtonFrame = 0;

	sf::Color colorMaskW = { 0,0,0};
	sf::Color colorMaskA = { 0,0,0 };
	sf::Color colorMaskS = { 0,0,0 };
	sf::Color colorMaskD = { 0,0,0 };

	int directionTracker = 0;
	int forwardTracker = 0;
	int leftTracker = 0;
	int rightTracker = 0;
	int backTracker = 0;

	int slashTracker = 0;
	int blockTracker = 0;
	int jumpTracker = 0;
	int flipTracker = 0;

	checkBox* detailed;
	TextButton* switchTabs;

	std::unique_ptr<Label> totalAPMLabel;
	std::unique_ptr<Label> recentAPMLabel;

	double recentAPM = 0.0;
	double totalAPM = 0.0;

	//Key MouseMovement;

	std::unique_ptr<checkBox> forward;
	std::unique_ptr<checkBox> back;
	std::unique_ptr<checkBox> left;
	std::unique_ptr<checkBox> right;

	std::unique_ptr<checkBox> jump;
	std::unique_ptr<checkBox> flip;

	std::unique_ptr<checkBox> attack;
	std::unique_ptr<checkBox> block;

	std::unique_ptr<TextButton> resetButton;


	sf::Texture bigCircleText;
	sf::Texture smallCircleText;
	sf::Sprite bigCircle;
	sf::Sprite smallCircle;

};


