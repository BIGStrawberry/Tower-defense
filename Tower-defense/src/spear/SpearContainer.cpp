#include "SpearContainer.h"

SpearContainer::SpearContainer(sf::RenderWindow& window):
	window(window),
	scoreText('0', font, 72)

{
	//*************************//
	//********LOAD SOUND*******//
	//*************************//
	if (!font.loadFromFile("resources/spear/fonts/consola.ttf")) {
		std::cout << "Could not load consola.ttf" << std::endl;
	}
	scoreText.setPosition({10, 10});

	//*************************//
	//********LOAD SOUND*******//
	//*************************//
	if (!thrustSoundBuffer.loadFromFile("resources/spear/sounds/thrust.wav")) {
		std::cout << "Could not load thrust.wav" << std::endl;
	}
	if (!defendSoundBuffer.loadFromFile("resources/spear/sounds/defend.wav")) {
		std::cout << "Could not load thrust.wav" << std::endl;
	}
	if (!clashSoundBuffer.loadFromFile("resources/spear/sounds/clash.wav")) {
		std::cout << "Could not load thrust.wav" << std::endl;
	}
	if (!hurtSoundBuffer.loadFromFile("resources/spear/sounds/hurt.wav")) {
		std::cout << "Could not load hurt.wav" << std::endl;
	}

	sounds.emplace_back(thrustSoundBuffer);
	sounds.emplace_back(defendSoundBuffer);
	sounds.emplace_back(clashSoundBuffer);
	sounds.emplace_back(hurtSoundBuffer);

	//*************************//
	//*****LOAD TEXTURES*******//
	//*************************//
	if (!bodyText.loadFromFile("resources/spear/textures/spear.png", sf::IntRect(0, 0, 32, 32))) {
		std::cout << "Could not load test.png" << std::endl;
	}
	if (!spearText.loadFromFile("resources/spear/textures/spear.png", sf::IntRect(32, 14, 64, 6))) {
		std::cout << "Could not load test.png" << std::endl;
	}
	if (!spearTipText.loadFromFile("resources/spear/textures/spear.png", sf::IntRect(96, 7, 13, 17))) {
		std::cout << "Could not load test.png" << std::endl;
	}

	sf::Sprite bodySprite(bodyText);
	bodySprite.setOrigin(static_cast<float>(bodyText.getSize().x) / 2, static_cast<float>(bodyText.getSize().y) / 2);

	sf::Sprite spearSprite(spearText);
	spearSprite.setOrigin(20, static_cast<float>(spearText.getSize().y) / 2 - 10);

	sf::Sprite spearTipSprite(spearTipText);
	spearTipSprite.setOrigin(-static_cast<float>(spearText.getSize().x) + 20, static_cast<float>(spearText.getSize().y) / 2 - 4);

	sprites.emplace_back(bodySprite);
	sprites.emplace_back(spearSprite);
	sprites.emplace_back(spearTipSprite);

	colors = {
		sf::Color{200, 33, 33},
		sf::Color{33, 33, 200},
		sf::Color{33, 200, 33},
		sf::Color{200, 200, 33}
	};

	positions = {
		sf::Vector2f{static_cast<float>(window.getSize().x) / 4, 50},
		sf::Vector2f{static_cast<float>(window.getSize().x) - static_cast<float>(window.getSize().x) / 4, static_cast<float>(window.getSize().y) - 50},
		sf::Vector2f{static_cast<float>(window.getSize().x) / 4, static_cast<float>(window.getSize().y) - 50},
		sf::Vector2f{static_cast<float>(window.getSize().x) - static_cast<float>(window.getSize().x) / 4, 50},
	};

 	constexpr const float PI = 3.141592654f;

	rotations = {
		PI / 4,
		PI + PI / 4,
		-PI / 4,
		PI - PI / 4
	};

	for (uint8_t i = 0; i <= MAX_SPEARMAN; ++i) {
		if (sf::Joystick::isConnected(i)) {
			uint8_t spearManId = i;
			spearMans[i] = std::make_unique<SpearMan>(window, sprites, sounds, colors[spearManId], spearManId, positions[spearManId], rotations[spearManId]);
			joystickPositions[i] = sf::Vector2f{0.0f, 0.0f};
		}
	}
}

void SpearContainer::update() {
	uint8_t deadCount = 0;
	for (auto& spearMan : spearMans) {
		if (spearMan.second->isDead()) {
			++deadCount;
			continue;
		}

		spearMan.second->update();


		// Colision
		for (auto& other : spearMans) {
			if (spearMan.first == other.first || other.second->isDead()) continue;

			spearMan.second->handleCollision(*other.second);
		}
	}

	// Only one standing
	if (spearMans.size() > 1 && deadCount == spearMans.size() - 1) {
		for (auto& spearMan : spearMans) {
			if (!spearMan.second->isDead()) {
				if (spearMan.second->id == lastWinner) {
					++winStreak;
				} else {
					lastWinner = spearMan.second->id;
					winStreak = 0;
				}
				scoreText.setString(std::to_string(winStreak));
			} else {
				uint8_t spearManId = spearMan.second->id;
				spearMans[spearManId] = std::make_unique<SpearMan>(window, sprites, sounds, colors[spearManId], spearManId, positions[spearManId], rotations[spearManId]);
			}
		}
	}
}

void SpearContainer::render() const {
	for (const auto& spearMan : spearMans) {
		spearMan.second->render();
	}

	window.draw(scoreText);
}

void SpearContainer::connectController(uint8_t controllerId) {
	uint8_t spearManId = controllerId;
	spearMans[controllerId] = std::make_unique<SpearMan>(window, sprites, sounds, colors[spearManId], spearManId, positions[spearManId]);
	joystickPositions[controllerId] = sf::Vector2f(0.0f, 0.0f);
}

void SpearContainer::disconnectController(uint8_t controllerId) {
	spearMans.erase(controllerId);
	joystickPositions.erase(controllerId);
}

void SpearContainer::onJoystickMoved(sf::Event& evt) {
	SpearMan* spearMan = spearMans[evt.joystickMove.joystickId].get();
	sf::Vector2f& joystickPosition = joystickPositions[evt.joystickMove.joystickId];
	bool movement = false;
	bool thrust = false;
	bool defend = false;
	const uint8_t threshhold = 75;


	switch (evt.joystickMove.axis) {
		// Left joystick on a xbox one controler
	case sf::Joystick::X:
		joystickPosition.x = static_cast<float>(evt.joystickMove.position);
		movement = true;
		break;
	case sf::Joystick::Y:
		joystickPosition.y = static_cast<float>(evt.joystickMove.position);
		movement = true;
		break;

		// Left and right trigger for xbox
		// For some reason the left and right trigger are on a axis and even worse they are on the same one
		// -100 = right trigger and 100 = left
	case sf::Joystick::Z:
		if (evt.joystickMove.position > threshhold && !spearMan->leftTriggerPressed) {
			spearMan->leftTriggerPressed = true;
			defend = true;
		} else if (evt.joystickMove.position < -threshhold && !spearMan->rightTriggerPressed) {
			spearMan->rightTriggerPressed = true;
			thrust = true;
			// Release checks for left and right trigger
		} else if (spearMan->rightTriggerPressed && evt.joystickMove.position > -threshhold) {
			spearMan->rightTriggerPressed = false;
		} else if (spearMan->leftTriggerPressed && evt.joystickMove.position < threshhold) {
			spearMan->leftTriggerPressed = false;
		}
		break;
		// Playstation left trigger
	case sf::Joystick::V:
		if (evt.joystickMove.position > threshhold && !spearMan->leftTriggerPressed) {
			spearMan->leftTriggerPressed = true;
			defend = true;
		} else if (spearMan->leftTriggerPressed && evt.joystickMove.position < threshhold) {
			spearMan->leftTriggerPressed = false;
		}
		break;
		// Playstation right trigger
	case sf::Joystick::U:
		if (evt.joystickMove.position > threshhold && !spearMan->rightTriggerPressed) {
			spearMan->rightTriggerPressed = true;
			thrust = true;
			// Release checks for left and right trigger
		} else if (spearMan->rightTriggerPressed && evt.joystickMove.position < threshhold) {
			spearMan->rightTriggerPressed = false;
		}
		break;
	}

	if (movement) {
		// Prevent SpearMan from changing derection when joystick is released
		if (joystickPosition.x < -threshhold || joystickPosition.x > threshhold || joystickPosition.y < -threshhold || joystickPosition.y > threshhold) {
			spearMan->setRotationJoystick(joystickPosition);
		}
	} else if (thrust) {
		spearMan->thrust();
	} else if (defend) {
		spearMan->defend();
	}
}
