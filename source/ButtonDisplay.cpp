#include "ButtonDisplay.h"
#include <fstream>

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

	
	tempPos = { 320,0 };	
	resetButton = std::make_unique<TextButton>("Reset", tempPos, 18, sf::Color::White, sf::Color::Black, bst, 1);
	tempPos = { 420, 0 };
	printButton = std::make_unique<TextButton>("Print", tempPos, 18, sf::Color::White, sf::Color::Black, bst, 1);

	tempPos = { 276, 100 };
	recentAPMLabel = std::make_unique<Label>(tempPos, 24, "Recent APM : ", 4, bst);
	tempPos = { 297, 120 };
	totalAPMLabel = std::make_unique<Label>(tempPos, 24, "Total APM : ", 4, bst);

	tempPos = { 420, 240 };
	WPrinter = std::make_unique<Label>(tempPos, 18, "", 4, bst);
	tempPos.y += 20;
	APrinter = std::make_unique<Label>(tempPos, 18, "", 4, bst);
	tempPos.y += 20;
	SPrinter = std::make_unique<Label>(tempPos, 18, "", 4, bst);
	tempPos.y += 20;
	DPrinter = std::make_unique<Label>(tempPos, 18, "", 4, bst);

	tempPos = { 600, 240 };
	WHeldPrinter = std::make_unique<Label>(tempPos, 18, "", 4, bst);
	tempPos.y += 20;
	AHeldPrinter = std::make_unique<Label>(tempPos, 18, "", 4, bst);
	tempPos.y += 20;
	SHeldPrinter = std::make_unique<Label>(tempPos, 18, "", 4, bst);
	tempPos.y += 20;
	DHeldPrinter = std::make_unique<Label>(tempPos, 18, "", 4, bst);

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
	if (flip->getChecked() != sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		flip->setChecked(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift));
		if (flip->getChecked()) {
			keyChanges++;
			flipTracker++;
		}
	}
	if (block->getChecked() != sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		block->setChecked(sf::Mouse::isButtonPressed(sf::Mouse::Right));
		if (block->getChecked()) {
			keyChanges++;
			blockTracker++;
		}
	}
	

	if (attack->getChecked() != sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		attack->setChecked(sf::Mouse::isButtonPressed(sf::Mouse::Left));
		if (attack->getChecked()) {
			keyChanges++;
			slashTracker++;
		}
		keyChanges += attack->getChecked();
	}
	if (forward->getChecked() != sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		forward->setChecked(sf::Keyboard::isKeyPressed(sf::Keyboard::W));
		if (forward->getChecked()) {
			keyChanges++;
			directionTracker++;
			forwardTracker++;
			forwardHoldTracker++;
			directionHoldTracker++;
			//std::cout << "colorMaskW.b : " << colorMaskW.b << std::endl;
		}
	}
	else if (forward->getChecked()) {
		forwardHoldTracker++;
		directionHoldTracker++;
	}
	if (left->getChecked() != sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		left->setChecked(sf::Keyboard::isKeyPressed(sf::Keyboard::A));
		if (left->getChecked()) {
			keyChanges++;
			directionTracker++;
			leftTracker++;
			leftHoldTracker++;
			directionHoldTracker++;

			//std::cout << "colorMaskA.b : " << colorMaskA.b << std::endl;
		}
	}
	else if (left->getChecked()) {
		leftHoldTracker++;
		directionHoldTracker++;
	}
	if (back->getChecked() != sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		back->setChecked(sf::Keyboard::isKeyPressed(sf::Keyboard::S));
		if (back->getChecked()) {
			keyChanges++;
			directionTracker++;
			backTracker++;
			backHoldTracker++;
			directionHoldTracker++;
			//std::cout << "colorMaskS.b : " << colorMaskS.b << std::endl;
		}
	}
	else if (back->getChecked()) {
		backHoldTracker++;
		directionHoldTracker++;
	}
	if (right->getChecked() != sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		right->setChecked(sf::Keyboard::isKeyPressed(sf::Keyboard::D));
		if (right->getChecked()) {
			keyChanges++;
			directionTracker++;
			rightTracker++;
			rightHoldTracker++;
			directionHoldTracker++;
			//std::cout << "colorMaskD.b : " << colorMaskD.b << std::endl;
		}
	}
	else if (right->getChecked()) {
		rightHoldTracker++;
		directionHoldTracker++;
	}
	if (jump->getChecked() != sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		jump->setChecked(sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
		if (jump->getChecked()) {
			keyChanges++;
			jumpTracker++;
		}
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
			std::ofstream file;
			if (directionTracker > 0) {
				file.open("button.log");
				float percentDirection = 0.0f;
				percentDirection = static_cast<float>(forwardTracker) / static_cast<float>(directionTracker);
				int percentPrinter = percentDirection * 1000;
				int percentDec = percentPrinter % 10;
				percentPrinter = percentDirection * 100;

				file << "W		- " << forwardTracker << " : " << percentPrinter << "." << percentDec << "%" << std::endl;
				percentDirection = static_cast<float>(leftTracker) / static_cast<float>(directionTracker);
				percentPrinter = percentDirection * 1000;
				percentDec = percentPrinter % 10;
				percentPrinter = percentDirection * 100;
				file << "A		- " << leftTracker << " : " << percentPrinter << "." << percentDec << "%" << std::endl;
				percentDirection = static_cast<float>(backTracker) / static_cast<float>(directionTracker);
				percentPrinter = percentDirection * 1000;
				percentDec = percentPrinter % 10;
				percentPrinter = percentDirection * 100;
				file << "S		- " << backTracker << " : " << percentPrinter << "." << percentDec << "%" << std::endl;
				percentDirection = static_cast<float>(rightTracker) / static_cast<float>(directionTracker);
				percentPrinter = percentDirection * 1000;
				percentDec = percentPrinter % 10;
				percentPrinter = percentDirection * 100;
				file << "D		- " << rightTracker << " : " << percentPrinter << "." << percentDec << "%" << std::endl;
				file << "shift	- " << flipTracker << std::endl;
				file << "jump	- " << jumpTracker << std::endl;
				file << "lmb		- " << slashTracker << std::endl;
				file << "rmb		- " << blockTracker << std::endl;


				percentDirection = static_cast<float>(forwardHoldTracker) / static_cast<float>(directionHoldTracker);
				percentPrinter = percentDirection * 1000;
				percentDec = percentPrinter % 10;
				percentPrinter = percentDirection * 100;
				file << "W Held		- " << forwardHoldTracker << " : " << percentPrinter << "." << percentDec << "%" << std::endl;
				percentDirection = static_cast<float>(leftHoldTracker) / static_cast<float>(directionHoldTracker);
				percentPrinter = percentDirection * 1000;
				percentDec = percentPrinter % 10;
				percentPrinter = percentDirection * 100;
				file << "A Held		- " << leftHoldTracker << " : " << percentPrinter << "." << percentDec << "%" << std::endl;
				percentDirection = static_cast<float>(backHoldTracker) / static_cast<float>(directionHoldTracker);
				percentPrinter = percentDirection * 1000;
				percentDec = percentPrinter % 10;
				percentPrinter = percentDirection * 100;
				file << "S Held		- " << backHoldTracker << " : " << percentPrinter << "." << percentDec << "%" << std::endl;
				percentDirection = static_cast<float>(rightHoldTracker) / static_cast<float>(directionHoldTracker);
				percentPrinter = percentDirection * 1000;
				percentDec = percentPrinter % 10;
				percentPrinter = percentDirection * 100;
				file << "D Held		- " << rightHoldTracker << " : " << percentPrinter << "." << percentDec << "%" << std::endl << std::endl;
				file.close();
			}

			window->close();
			break;
		}


		case sf::Event::MouseButtonPressed: {
			if (event.mouseButton.button == sf::Mouse::Left) {

				//detailed->isMouseOver(*window);
				if (detailedActive != detailed->getChecked()) {
					detailedActive = !detailedActive;
				}
				if (switchTabs->isMouseOver(*window)) {
					currentTab = 2;
				}
				if (resetButton->isMouseOver(*window)) {
					directionTracker = 0;
					forwardTracker = 0;
					leftTracker = 0;
					backTracker = 0;
					rightTracker = 0;

					totalButtonsPressed = 0;
					recentButtonsPressed = 0;
					totalButtonFrames = 0;
					currentButtonFrame = 0;
				};

				if (printButton->isMouseOver(*window)) {
					if (directionTracker > 0) {
						printTracker();
					}
				}
				//forward->isMouseOver(*window);
				
				

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
	if (directionTracker > 0) {
		float percentDirection = static_cast<float>(forwardTracker) / static_cast<float>(directionTracker);
		if (percentDirection > 0.33f) {
			colorMaskW.r = 0;
			colorMaskW.b = 255 - ((percentDirection - 0.33f) * 255);
		}
		else {
			colorMaskW.r = percentDirection * 4 * 128;
			colorMaskW.b = 0;
		}
		//std::cout << "w percentDirection : " << percentDirection << std::endl;

		percentDirection = static_cast<float>(leftTracker) / static_cast<float>(directionTracker);
		if (percentDirection > 0.33f) {
			colorMaskA.r = 0;
			colorMaskA.b = 255 - ((percentDirection - 0.33f) * 255);
		}
		else {
			colorMaskA.r = percentDirection * 4 * 128;
			colorMaskA.b = 0;
		}
		//std::cout << "a percentDirection : " << percentDirection << std::endl;
		
		percentDirection = static_cast<float>(backTracker) / static_cast<float>(directionTracker);
		if (percentDirection > 0.33f) {
			colorMaskS.r = 0;
			colorMaskS.b = 255 - ((percentDirection - 0.33f) * 255);
		}
		else {
			colorMaskS.r = percentDirection * 4 * 128;
			colorMaskS.b = 0;
		}
		//std::cout << "s percentDirection : " << percentDirection << std::endl;
		
		percentDirection = static_cast<float>(rightTracker) / static_cast<float>(directionTracker);
		if (percentDirection > 0.33f) {
			colorMaskD.r = 0;
			colorMaskD.b = 255 - ((percentDirection - 0.33f) * 255);
		}
		else {
			colorMaskD.r = percentDirection * 4 * 128;
			colorMaskD.b = 0;
		}
		//std::cout << "d percentDirection : " << percentDirection << std::endl;
	}

	forward->setSpriteColor(colorMaskW);
	left->setSpriteColor(colorMaskA);
	back->setSpriteColor(colorMaskS);
	right->setSpriteColor(colorMaskD);

	forward->draw(*window);
	left->draw(*window);
	back->draw(*window);
	right->draw(*window);

	jump->draw(*window);
	flip->draw(*window);

	attack->draw(*window);
	block->draw(*window);

	resetButton->draw(*window);
	printButton->draw(*window);

	window->draw(bigCircle);
	window->draw(smallCircle);

	recentAPMLabel->drawTo(*window);
	totalAPMLabel->drawTo(*window);


	WPrinter->drawTo(*window);
	APrinter->drawTo(*window);
	SPrinter->drawTo(*window);
	DPrinter->drawTo(*window);

	WHeldPrinter->drawTo(*window);
	AHeldPrinter->drawTo(*window);
	SHeldPrinter->drawTo(*window);
	DHeldPrinter->drawTo(*window);
}

void ButtonDisplay::printTracker() {
	float percentDirection = static_cast<float>(forwardTracker) / static_cast<float>(directionTracker);
	int percentPrinter = percentDirection * 1000;
	int percentDec = percentPrinter % 10;
	percentPrinter = percentDirection * 100;

	//WPrinter. << "W		- " << forwardTracker << " : " << percentPrinter << "." << percentDec << "%" << std::endl;
	std::string tempString = "W		- ";
	tempString += std::to_string(forwardTracker);
	tempString += " : ";
	tempString += std::to_string(percentPrinter);
	tempString += ".";
	tempString += std::to_string(percentDec);
	tempString += "%";
	WPrinter->setText(tempString);

	percentDirection = static_cast<float>(leftTracker) / static_cast<float>(directionTracker);
	percentPrinter = percentDirection * 1000;
	percentDec = percentPrinter % 10;
	percentPrinter = percentDirection * 100;

	tempString = "A		- ";
	tempString += std::to_string(leftTracker);
	tempString += " : ";
	tempString += std::to_string(percentPrinter);
	tempString += ".";
	tempString += std::to_string(percentDec);
	tempString += "%";
	APrinter->setText(tempString);
	//file << "A		- " << leftTracker << " : " << percentPrinter << "." << percentDec << "%" << std::endl;
	percentDirection = static_cast<float>(backTracker) / static_cast<float>(directionTracker);
	percentPrinter = percentDirection * 1000;
	percentDec = percentPrinter % 10;
	percentPrinter = percentDirection * 100;

	tempString = "S		- ";
	tempString += std::to_string(backTracker);
	tempString += " : ";
	tempString += std::to_string(percentPrinter);
	tempString += ".";
	tempString += std::to_string(percentDec);
	tempString += "%";
	SPrinter->setText(tempString);
	//file << "S		- " << backTracker << " : " << percentPrinter << "." << percentDec << "%" << std::endl;
	percentDirection = static_cast<float>(rightTracker) / static_cast<float>(directionTracker);
	percentPrinter = percentDirection * 1000;
	percentDec = percentPrinter % 10;
	percentPrinter = percentDirection * 100;

	tempString = "D		- ";
	tempString += std::to_string(rightTracker);
	tempString += " : ";
	tempString += std::to_string(percentPrinter);
	tempString += ".";
	tempString += std::to_string(percentDec);
	tempString += "%";
	DPrinter->setText(tempString);




	percentDirection = static_cast<float>(forwardHoldTracker) / static_cast<float>(directionHoldTracker);
	percentPrinter = percentDirection * 1000;
	percentDec = percentPrinter % 10;
	percentPrinter = percentDirection * 100;
	tempString = "W Held	- ";
	tempString += std::to_string(forwardHoldTracker);
	tempString += " : ";
	tempString += std::to_string(percentPrinter);
	tempString += ".";
	tempString += std::to_string(percentDec);
	tempString += "%";
	WHeldPrinter->setText(tempString);

	percentDirection = static_cast<float>(leftHoldTracker) / static_cast<float>(directionHoldTracker);
	percentPrinter = percentDirection * 1000;
	percentDec = percentPrinter % 10;
	percentPrinter = percentDirection * 100;

	tempString = "A Held	- ";
	tempString += std::to_string(leftHoldTracker);
	tempString += " : ";
	tempString += std::to_string(percentPrinter);
	tempString += ".";
	tempString += std::to_string(percentDec);
	tempString += "%";
	AHeldPrinter->setText(tempString);
	//file << "A		- " << leftHoldTracker << " : " << percentPrinter << "." << percentDec << "%" << std::endl;
	percentDirection = static_cast<float>(backHoldTracker) / static_cast<float>(directionHoldTracker);
	percentPrinter = percentDirection * 1000;
	percentDec = percentPrinter % 10;
	percentPrinter = percentDirection * 100;

	tempString = "S Held	- ";
	tempString += std::to_string(backHoldTracker);
	tempString += " : ";
	tempString += std::to_string(percentPrinter);
	tempString += ".";
	tempString += std::to_string(percentDec);
	tempString += "%";
	SHeldPrinter->setText(tempString);
	//file << "S		- " << backHoldTracker << " : " << percentPrinter << "." << percentDec << "%" << std::endl;
	percentDirection = static_cast<float>(rightHoldTracker) / static_cast<float>(directionHoldTracker);
	percentPrinter = percentDirection * 1000;
	percentDec = percentPrinter % 10;
	percentPrinter = percentDirection * 100;

	tempString = "D Held	- ";
	tempString += std::to_string(rightHoldTracker);
	tempString += " : ";
	tempString += std::to_string(percentPrinter);
	tempString += ".";
	tempString += std::to_string(percentDec);
	tempString += "%";
	DHeldPrinter->setText(tempString);
}