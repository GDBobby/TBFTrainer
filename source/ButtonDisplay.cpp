#include "ButtonDisplay.h"


ButtonDisplay::ButtonDisplay(sf::RenderWindow* windowPtr, sf::Font& bst, checkBox* detailBox, bool detailedBool, TextButton* tabSwitcher) {
	window = windowPtr;
	detailed = detailBox;
	detailedActive = detailedBool;
	switchTabs = tabSwitcher;

	sf::Vector2f tempPos = { 148,100 };
	sf::Vector2i spriteSize = { 128,128 };
	sf::Vector2f relPos = { 70,60 };
	forward = std::make_unique<checkBox>("W", tempPos, bst, 0, "Keys.png", spriteSize, relPos);

	tempPos = { 148, 228 };
	back = std::make_unique<checkBox>("S", tempPos, bst, 0, "Keys.png", spriteSize, relPos);

	tempPos = { 20, 228 };
	left = std::make_unique<checkBox>("A", tempPos, bst, 0, "Keys.png", spriteSize, relPos);

	tempPos = { 276, 228 };
	right = std::make_unique<checkBox>("D", tempPos, bst, 0, "Keys.png", spriteSize,relPos);

	tempPos = {276, 356};
	relPos = { 90, 60 };
	jump = std::make_unique<checkBox>("Space", tempPos, bst, 0, "Keys.png", spriteSize, relPos);

	tempPos = { 20,356 };
	relPos = { 80, 60 };
	flip = std::make_unique<checkBox>("Shift", tempPos, bst, 0, "Keys.png", spriteSize, relPos);

	tempPos = { 468, 84 };
	attack = std::make_unique<checkBox>("", tempPos, bst, 0, "leftClick.png", spriteSize);

	tempPos = { 596, 84 };
	block = std::make_unique<checkBox>("", tempPos, bst, 0, "rightClick.png", spriteSize);

	tempPos = { 276, 100 };
	recentAPMLabel = std::make_unique<Label>(tempPos, 24, "Recent APM : ", 4, bst);
	tempPos = { 297, 120 };
	totalAPMLabel = std::make_unique<Label>(tempPos, 24, "Total APM : ", 4, bst);


	//saving this for later, when i figure out how to do it properly
	//bigCircleText.loadFromFile("circle.png");
	//smallCircleText.loadFromFile("smallCircle.png");

	//smallCircle.setTexture(smallCircleText);
	//bigCircle.setTexture(bigCircleText);

	//smallCircle.setPosition(spriteCenter);
	//bigCircle.setPosition({ 468, 228 });

}

void ButtonDisplay::resize() {
	window->setSize({ 800, 500 });
	sf::FloatRect visibleArea(0.f, 0.f, 800.f, 500.f);
	window->setView(sf::View(visibleArea));
}

void ButtonDisplay::update() {

	char keyChanges = 0;
	if (rmbBlock) {
		if (flip->getChecked() != sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
			flip->setChecked(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift));
			keyChanges += flip->getChecked();
		}
		if (block->getChecked() != sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			block->setChecked(sf::Mouse::isButtonPressed(sf::Mouse::Right));
			keyChanges += block->getChecked();
		}
	}
	else {
		if (flip->getChecked() != sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			flip->setChecked(sf::Mouse::isButtonPressed(sf::Mouse::Right));
			keyChanges += flip->getChecked();
		}
		if (block->getChecked() != sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
			block->setChecked(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift));
			keyChanges += block->getChecked();
		}
	}

	if (attack->getChecked() != sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		attack->setChecked(sf::Mouse::isButtonPressed(sf::Mouse::Left));
		keyChanges += attack->getChecked();
	}
	if (forward->getChecked() != sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		forward->setChecked(sf::Keyboard::isKeyPressed(sf::Keyboard::W));
		keyChanges += forward->getChecked();
	}
	if (left->getChecked() != sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		left->setChecked(sf::Keyboard::isKeyPressed(sf::Keyboard::A));
		keyChanges += left->getChecked();
	}
	if (back->getChecked() != sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		back->setChecked(sf::Keyboard::isKeyPressed(sf::Keyboard::S));
		keyChanges += back->getChecked();
	}
	if (right->getChecked() != sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		right->setChecked(sf::Keyboard::isKeyPressed(sf::Keyboard::D));
		keyChanges += right->getChecked();
	}
	if (jump->getChecked() != sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		jump->setChecked(sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
		keyChanges += jump->getChecked();
	}

	totalButtonsPressed += keyChanges;
	if (totalButtonFrames < ARRAYSIZE) {
		totalAPM = totalButtonsPressed * 15000 / (totalButtonFrames + 1);
		recentAPM = totalAPM;
		recentButtonsPressed = totalButtonsPressed;
	}
	else {
		//std::cout << "old : new  ~ " << +apmArray[currentButtonFrame] << ":" << +keyChanges << std::endl;
		recentButtonsPressed += (keyChanges - apmArray[currentButtonFrame]);
		recentAPM = recentButtonsPressed;
		totalAPM = totalButtonsPressed * 15000 / (totalButtonFrames + 1);
	}

	int tempRecentAPM = recentAPM;
	int tempTotalAPM = totalAPM;

	std::string tempString = "Recent APM : ";
	tempString += std::to_string(tempRecentAPM);
	recentAPMLabel->setText(tempString);

	tempString = "Total APM : ";
	tempString += std::to_string(tempTotalAPM);
	totalAPMLabel->setText(tempString);

	//std::cout << "Total Buttons Pressed : " << totalButtonsPressed << " ~ ";
	//std::cout << " Recent Buttons Pressed : " << recentButtonsPressed << std::endl;
	//std::cout << "recent : total : " << recentAPM << ":" << totalAPM << std::endl;

	apmArray[currentButtonFrame] = keyChanges;
	currentButtonFrame++;
	totalButtonFrames++;
	if (currentButtonFrame == ARRAYSIZE) {
		//std::cout << "reset?" << std::endl;
		currentButtonFrame = 0;
	}


	/* for a later date, can't get this to work properly
	if (hasFocus) {
		sf::Vector2i mouseCurrent = sf::Mouse::getPosition();
		sf::Vector2f mouseDiff = { static_cast<float>(mouseLast.x - mouseCurrent.x), static_cast<float>(mouseLast.y - mouseCurrent.y) };
		mouseLast = mouseCurrent;

		if (mouseDiff.x != 0.f) {
			std::cout << mouseDiff.x << std::endl;
		}

		smallCircle.setPosition(spriteCenter - (mouseDiff * 2.f));
		//std::cout << "has focus" << std::endl;
		//std::cout << "mouse position : " << mousePos.x << ":" << mousePos.y << std::endl;
	}
	else {
		if (mouseUpdate) {
			sf::Vector2i mouseCurrent = sf::Mouse::getPosition();

			if(mouseCurrent == mouseLast)
			mouseUpdateFrames++;
			if (mouseUpdateFrames > 250) {
				mouseLast = sf::Mouse::getPosition();
				mouseUpdate = false;
			}
			mouseLast = mouseCurrent;

		}
		sf::Vector2i mouseCurrent = sf::Mouse::getPosition();

		
		sf::Vector2f mouseDiff = { static_cast<float>(mouseLast.x - mouseCurrent.x), static_cast<float>(mouseLast.y - mouseCurrent.y) };

		std::cout << mouseDiff.x << ":" << mouseDiff.y << std::endl;

		smallCircle.setPosition(spriteCenter - (mouseDiff * 2.f));
	}
	*/
	

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

				detailed->isMouseOver(*window);
				if (detailedActive != detailed->getChecked()) {
					detailedActive = !detailedActive;
				}
				if (switchTabs->isMouseOver(*window)) {
					currentTab = 2;
				}
				forward->isMouseOver(*window);

				
				

				//metronomeSpeed.setActivity(metronomeSpeed.isMouseOver(mainWindow));

			}
			break;
		}
		case sf::Event::LostFocus:{
			hasFocus = false;
			mouseUpdate = true;
			mouseUpdateFrames = 0;

			break;
			//std::cout << "mouse move : " << event.mouseMove.x << ":" << event.mouseMove.y << std::endl;
		}
		case sf::Event::GainedFocus: {
			hasFocus = true;
			break;
		}

		default: {
			break;
		}
		}
	}
}

void ButtonDisplay::draw() {
	forward->draw(*window);
	left->draw(*window);
	back->draw(*window);
	right->draw(*window);

	jump->draw(*window);
	flip->draw(*window);

	attack->draw(*window);
	block->draw(*window);

	window->draw(bigCircle);
	window->draw(smallCircle);

	recentAPMLabel->drawTo(*window);
	totalAPMLabel->drawTo(*window);
}