#pragma once
#include <cstdint>
#include <SFML/graphics.hpp>

/**
* @class Player
* @file Player.hpp
* @brief Class for the Player
*/
class Player {
private:
	sf::RenderWindow & window;

public:
	/**
	* @brief Player Constructor
	* @param window		SFML window instance
	* @param lives		amount of lives the player has
	* @param gold		amount of gold the player has
	* @param score		amount of score the player has
	*/
	Player(sf::RenderWindow & window, uint8_t lives, uint32_t gold, uint32_t score);

	/**
	* @brief Public variable for the amount of lives the player has
	*/
	uint8_t lives;

	/**
	* @brief Public variable for the amount of gold the player has
	*/
	uint32_t gold;

	/**
	* @brief Public variable for the amount of score the player has
	*/
	uint32_t score;
};