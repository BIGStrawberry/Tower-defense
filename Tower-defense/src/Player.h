#pragma once
#include <cstdint>
#include <vector>
#include <SFML/graphics.hpp>
#include "Action/Action.h"

/**
* @class Player
* @file Player.cpp
* @brief Class for the Player
*/
class Player {
private:
	/**
	* @brief SFML window instance
	*/
	sf::RenderWindow & window;
	/**
	* @brief Amount of actions the player has made since the last wave
	* @description Must be cleared everytime a new wave spawns, to prevent players undo-ing all actions for free
	*/
	uint32_t numActions;

	/**
	* @brief Public variable for the amount of gold the player has
	*/
	int32_t gold, accumulatedGold;
	
public:
	/**
	* @brief Player Constructor
	* @param window		SFML window instance
	* @param lives		amount of lives the player has
	* @param gold		amount of gold the player has
	*/
	Player(sf::RenderWindow & window, uint8_t lives, uint32_t startingGold);

	/**
	* @brief A vector containing all the actions performed by the player
	*/
	std::vector<Action> actions;

	/**
	* @brief Public variable for the amount of lives the player has
	*/
	int8_t lives;

	/*
	* @brief Public variable to track the amount of towers placed on the grid
	*/
	uint32_t numberOfTowersPlaced = 0;
	/*
	* @brief Public variable to track the amount of towers the player has upgraded
	*/
	uint32_t numberOfTowersUpgraded = 0;
	/*
	* @brief Public variable to track the amount of enemies killed
	*/
	uint32_t numberOfEnemiesKilled = 0;
	/*
	* @brief Public variable to track the amount of waves completed
	*/
	uint32_t numberOfWavesCompleted = 0;


	/**
	* @brief Function to add gold to the variable gold
	*/
	void addGold(int32_t amount, bool increase_accumulated = true);

	/**
	* @brief Function to remove gold to the variable gold
	*/
	void removeGold(int32_t amount);

	/**
	* @brief Function to reset the variable gold to the accumulatedGold
	*/
	void resetGold();

	/**
	* @brief Function to get the amount of gold the player has
	*/
	int32_t getGold();

	/**
	* @brief Function to get the accumulated gold of the player
	*/
	int32_t getAccumulatedGold();

	/**
	* @brief Adds an action to the action vector
	* @param x	-	x position of the tower which the action was used on
	* @param y	-	y position of the tower which the action was used on
	* @param type	-	type of the tower the action was performed on
	* @param cost	- amount of gold the action has cost
	*/
	void addAction(uint8_t x, uint8_t y, uint32_t cost, Action::ACTION_TYPE type, TowerType tower_type);

	/**
	* @brief Removes the last action from the actions vector
	*/
	void undoAction();

	/**
	* @brief Resets the variable numActions to 0
	*/
	void resetNumActions();
};