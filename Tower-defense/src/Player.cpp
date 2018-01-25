#include "Player.h"

Player::Player(sf::RenderWindow & window, uint8_t lives, uint32_t startingGold):
	window(window),
	lives(lives),
	gold(startingGold),
	accumulatedGold(startingGold)
{}


void Player::addGold(int32_t amount) {
	gold += amount;
	accumulatedGold += amount;
}

void Player::resetGold() {
	gold = accumulatedGold;
}

int32_t Player::getGold() {
	return gold;
}

int32_t Player::getAccumulatedGold() {
	return accumulatedGold;
}

void Player::removeGold(int32_t amount) {
	gold -= amount;
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

