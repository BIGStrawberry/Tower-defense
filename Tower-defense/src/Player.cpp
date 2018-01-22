#include "Player.h"

Player::Player(sf::RenderWindow & window, uint8_t lives, uint32_t gold, uint32_t score):
	window(window),
	lives(lives),
	gold(gold),
	score(score) {}


void Player::addAction(uint8_t x, uint8_t y, Action::ACTION_TYPE type, uint32_t actionCost) {
	actions.emplace_back(x, y, type, actionCost);
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

