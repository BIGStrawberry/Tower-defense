#pragma once
#include <cstdint>

/**
* @class Action
* @file Action.h
* @brief Used to save player made actions
*/
class Action  {
public:
	/**
	* @brief Enum of action types
	*/
	enum class ACTION_TYPE {
		SELL_TOWER,
		UPGRADE_TOWER,
		PLACE_TOWER
	};	
	
	/**
	* @brief cost of the action
	*/
	uint32_t actionCost;

	/**
	* @brief indexes in grid of the action performed
	*/
	uint8_t x,y;

	/**
	* @brief type of action
	*/
	ACTION_TYPE type;

	/**
	* @brief Constructor
	* @param index - index for the tower affected in the action
	* @param type - The type of action the player made
	* @param actionCost - Amount of gold the player paid or received from the action
	*/
	Action(uint8_t x, uint8_t y, ACTION_TYPE type, uint32_t actionCost);
};