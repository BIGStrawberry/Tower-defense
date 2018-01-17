#include "Player.cpp"

/**
* @class Player
* @file Player.h
* @brief Class for the Player
* @details Keeps track of variables the player has like lives, gold and a score
*/
Player::Player(sf::RenderWindow & window, uint8_t lives, uint32_t gold, uint32_t score):
	window(window),
	lives(lives),
	gold(gold),
	score(score) {}