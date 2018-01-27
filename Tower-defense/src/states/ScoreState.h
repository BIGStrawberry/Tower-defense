#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "PlayState.h"
#include "MenuState.h"
#include "../Player.h"
#include "../helpers/Menu.h"
#include "../helpers/MenuItem.h"

class ScoreState: public State {
private:
	sf::Font font;
	sf::Text scoreText, scoreEnemiesKilled, scoreTowersPlaced, scoreWavesCompleted,  scoreTowersUpgraded, scoreAccumulatedGold;
	Menu menu;
	const Player & player;
public:
	ScoreState(sf::RenderWindow& window, const Player & player);

	/**
	* @brief Function to calculate the score the player has
	* @param player - player object to calculate the score for
	* @details We give this function the player object because otherwise we get a nullptr exception
		because we use this function in the initialize list
	*/
	uint32_t calculateScore(const Player & player);

	void init() override;
	void update() override;
	void render() const override;
	void cleanUp() override;

	void onKeyPressed(sf::Event& evt) override;
	void onMouseButtonPressed(sf::Event& evt) override;
	void onMouseMoved(sf::Event& evt) override;
};