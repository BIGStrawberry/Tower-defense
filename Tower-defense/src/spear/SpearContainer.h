#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <array>
#include <unordered_map>
#include <memory>
#include "SpearMan.h"
#include "../helpers/Menu.h"

class SpearContainer {
private:
	static constexpr uint8_t MAX_SPEARMAN = 4;
	std::vector<sf::Sprite> sprites;
	sf::Texture bodyText, spearText, spearTipText;
	
	std::vector<sf::Sound> sounds;
	sf::SoundBuffer thrustSoundBuffer, defendSoundBuffer, clashSoundBuffer, hurtSoundBuffer;
	
	sf::RenderWindow& window;

	std::unordered_map<uint8_t, std::unique_ptr<SpearMan>> spearMans;
	std::unordered_map<uint8_t, sf::Vector2f> joystickPositions;
	std::array<sf::Color, MAX_SPEARMAN> colors;
	std::array<sf::Vector2f, MAX_SPEARMAN> positions;
	std::array<float, MAX_SPEARMAN> rotations;

	sf::Font font;
	sf::Text scoreText;
	uint8_t lastWinner = MAX_SPEARMAN + 1;
	uint8_t winStreak = 0;
public:
	explicit SpearContainer(sf::RenderWindow& window);

	void connectController(uint8_t controllerId);
	void disconnectController(uint8_t controllerId);

	void update();
	void render() const;

	void onJoystickMoved(sf::Event& evt);
};

