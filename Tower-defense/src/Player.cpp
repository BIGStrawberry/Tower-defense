#include "Player.h"

Player::Player(sf::RenderWindow & window, uint8_t lives, uint32_t startingGold):
	window(window),
	lives(lives),
	startingGold(startingGold),
	gold(startingGold) 
{
	numberOfEnemiesKilled = 0;
	numberOfTowersPlaced = 0;
	numberOfTowersUpgraded = 0;
	numberOfWavesCompleted = 0;
}


void Player::addAction(uint8_t x, uint8_t y, uint32_t actionCost, Action::ACTION_TYPE type, TowerType tower_type) {
	actions.emplace_back(x, y, actionCost, type, tower_type);
	numActions++;
}

void Player::undoAction() {
	if (numActions > 0) {
		actions.pop_back();
		numActions--;
	}
}

void Player::resetNumActions() {
	numActions = 0;
}

