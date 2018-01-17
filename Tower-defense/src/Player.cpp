#include "Player.h"

Player::Player(sf::RenderWindow & window, uint8_t lives, uint32_t gold, uint32_t score):
	window(window),
	lives(lives),
	gold(gold),
	score(score) {}