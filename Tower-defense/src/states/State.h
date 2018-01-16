#pragma once

#include <SFML/Graphics.hpp>

/**
* @class State
* @file State.hpp
* @brief Abstract super class for states.
*
* @details
* This class is used to create different game states.
* The GameStateManager calls the init when whe state is created and calls the cleanUp when the state is destructed.
* The game loop calls the update and render.
*
*/
class State {
protected:
	/**
	* SFML window to draw on
	*/
	sf::RenderWindow& window;
public:
	/**
	* @brief Constructor
	* @param window SFML window to draw on
	*
	*/
	State(sf::RenderWindow& window): window(window) {}

	/**
	* @brief Initializes the state
	*/
	virtual void init() = 0;
	/**
	* @brief Updates the state
	*/
	virtual void update() = 0;
	/**
	* @brief Renders the state on the window
	*/
	virtual void render() const = 0;
	/**
	* @brief Cleans up the state
	*/
	virtual void cleanUp() = 0;
};