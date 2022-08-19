#pragma once
#include "TextButton.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

//std lib
#include <memory>

class TbfTrainer
{
public:
	TbfTrainer(sf::RenderWindow* windowPtr, sf::Font& bst, checkBox* detailBox, bool detailedBool, TextButton* tabSwitcher);

	void update();
	void draw();
	void resize();

	const float mainWidth = 400.f; //this should be changed to pass by reference later
	const float mainHeight = 500.f;
	bool detailedActive;
	char currentTab = 0;

private:
	sf::RenderWindow *window;
	sf::Sound sound;

	checkBox* detailed;
	TextButton* switchTabs;

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


	std::unique_ptr<Label> slashDown;
	std::unique_ptr<Label> slashTimeL;
	std::unique_ptr<Label> blockDown;
	std::unique_ptr<Label> blockTimeL;

	std::unique_ptr<checkBox> jumpReset;
	std::unique_ptr<Label> jumpSlashLabel;
	std::unique_ptr<Label> jumpSlash;

	std::unique_ptr<Label> betweenLabel;
	std::unique_ptr<Label> timeBetweenSB;

	std::unique_ptr<Label> currentSpeedLabel;
	std::unique_ptr<Label> currentSpeed;


	std::unique_ptr<Label> timeIdleSlashLabel;
	std::unique_ptr<Label> timeIdleSlash;

	std::unique_ptr<Label> SlashFailLabel;
	std::unique_ptr<Label> SlashFail;

	std::unique_ptr<Label> AverageLabel;
	std::unique_ptr<Label> AverageSpeed;

	std::unique_ptr<Textbox> metronomeSpeed;
	std::unique_ptr<checkBox> metronomeCheck;
	
};