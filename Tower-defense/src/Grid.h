#pragma once
#include <SFML/graphics.hpp>
#include <array>
#include <memory>
#include <vector>

/**
* @class Grid
* @file Grid.h
* @brief Class for the Grid
*/
class Grid {
private:
	/**
	* @brief xOffset		The amount of space between the left screen boarder and the grid
	*/
	const float xOffset = 64;
	/**
	* @brief yOffset		The amount of space between the top screen boarder and the grid
	*/
	const float yOffset = 72;

	/**
	* @brief COLUMNS		The mounts of columns the grid has
	*/
	static constexpr const uint8_t COLUMNS = 36;

	/**
	* @brief ROWS			The mounts of ROWS the grid has
	*/
	static constexpr const uint8_t ROWS = 18;

	/**
	* @brief tileSize		The length and with of the grid tiles
	*/
	float tileSize;

	/**
	* @brief spawn			The place where enemy's spawn
	*/
	sf::RectangleShape spawn;

	/**
	* @brief base			The place where enemy's need to go
	*/
	sf::RectangleShape base;

	/**
	* @brief window			The window where everything will be drawn to
	*/
	sf::RenderWindow & window;

	/**
	* @brief towers			An array where all the placed towers will be stored in
	*/
	std::array<std::shared_ptr<sf::RectangleShape>, COLUMNS * ROWS > towers;

	/**
	* @brief enemies		An array where all the 'living' will be stored in
	*/
	std::vector<sf::CircleShape> enemies;

	/**
	* @brief waveQueue		An array where all the enemies that need to spawn in the next wave will be stored in 
	*/
	std::vector<sf::CircleShape> waveQueue;
public:
	/**
	* @brief Grid Constructor
	* @param window			SFML window instance
	* @param tileSize		The size of the grid tiles
	*/
	Grid(sf::RenderWindow & window, float tileSize);

	/**
	* @brief Renders the enemy and tower objects
	*/
	void render() const;

	/**
	* @brief Places towers on the target grid location
	* @param x				The x-coordinate where the tower needs to be placed
	* @param y				The y-coordinate where the tower needs to be placed
	* @param newTower		The tower that needs to be placed on said coordinated
	*/
	bool placeTower(uint8_t x, uint8_t y, std::shared_ptr<sf::RectangleShape> newTower);
};
