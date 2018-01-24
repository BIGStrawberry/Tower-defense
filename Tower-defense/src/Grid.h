#pragma once
#include <SFML/graphics.hpp>
#include <memory>
#include <random>
#include <array>
#include <vector>
#include "tower\Tower.h"
#include "tower\make_tower.h"
#include "Enemy\Enemy.h"
#include "Enemy\EnemyType.h"
#include "Player.h"
#include "Pathfinding\Pathfinder.h"

/**
* @class Grid
* @file Grid.h
* @brief Class for the Grid
*/
class Grid {
private:
	/**
	* @ brief the wave  
	*/
	uint16_t waveNumber = 1;
	/**
	* @brief Spawning rate (0 - 100%), First wave the enemy can appear and the number of enemies that span per groep (there can be multiple groups per wave)
	*/
	static constexpr const uint8_t FLYING_SPAWN_RATE = 25, FAST_SPAWN_RATE = 85, NORMAL_SPAWN_RATE = 100, TANK_SPAWN_RATE = 100;
	static constexpr const uint8_t FLYING_START_WAVE = 15, FAST_START_WAVE = 10, NORMAL_START_WAVE = 1,   TANK_START_WAVE = 5;
	static constexpr const uint8_t FLYING_PER_GROUP  = 3,  FAST_PER_GROUP  = 5,  NORMAL_PER_GROUP  = 6,   TANK_PER_GROUP  = 4;
	/**
	* @details Clock for pre-wave build time
	*/
	sf::Clock waveClock;
	sf::Time waveDelay = sf::seconds(30);
	bool preWave = true;

	/**
	* @brief xOffset		The amount of space between the left screen boarder and the grid
	*/
	const float xOffset = 80;
	/**
	* @brief yOffset		The amount of space between the top screen boarder and the grid
	*/
	const float yOffset = 88;

	/**
	* @brief clock			A Clock object used for tracking the elapsed time between enemy spawns
	*/
	sf::Clock clock;

	/**
	* @brief spawnDelay		The amount of time in ms that needs to pass before an enemy can spawn
	*/
	sf::Time spawnDelay = sf::milliseconds(500);

	/**
	* @brief COLUMNS		The mounts of columns the grid has
	*/
	static constexpr const uint8_t COLUMNS = 36;

	/**
	* @brief ROWS			The mounts of ROWS the grid has
	*/
	static constexpr const uint8_t ROWS = 18;

	/**
	* @brief Index of spawning point in grid array
	*/
	static constexpr const uint16_t START_INDEX = 0 + 9 * COLUMNS;
	/**
	* @brief Index of base point in grid array
	*/
	static constexpr const uint16_t END_INDEX = COLUMNS - 1 + 9 * COLUMNS;

	/**
	* @brief tileSize		The length and with of the grid tiles
	*/
	float tileSize;

	/**
	* @brief lineSize		The width of the lines between the grid
	*/
	float lineSize = 1;

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
	std::array<std::shared_ptr<Tower>, COLUMNS * ROWS > grid;

	/**
	* @brief enemies		An array where all the 'living' will be stored in
	*/
	std::vector<std::shared_ptr<Enemy>> enemies;

	/**
	* @brief waveQueue		An array where all the enemies that need to spawn in the next wave will be stored in 
	*/
	std::vector<std::shared_ptr<Enemy>> waveQueue;

	/**
	* @brief player			An player object of the player that is playing the game
	*/
	Player& player;

	/**
	* @brief pathfinding object
	*/
	Pathfinder<COLUMNS * ROWS> pathfinder;

	/**
	* @brief The path that enemies follow
	*/
	std::vector<sf::Vector2f> path;

public:
	/**
	* @brief Grid Constructor
	* @param window			SFML window instance
	* @param tileSize		The size of the grid tiles
	*/
	Grid(sf::RenderWindow & window, float tileSize, Player & player);

	/**
	* @brief Getter for preWave
	*/
	bool isInPreWave() const {
		return preWave;
	}

	/**
	* @brief Updates the enemy and tower objects
	*/
	void update();

	/**
	* @brief Renders the enemy and tower objects
	*/
	void render() const;

	/**
	* @brief Calculates and sets path
	* @details
	* Uses the PathFinder class to calculate the path
	*/
	void calculatePath();
	/**
	* @brief Starts the wave
	* @details
	* Generates a new wave and adds it to the waveQueue
	*/
	void startWave();

	/**
	* @brief Checks if a tower can be placed at x,y
	* @param x				The x-index where the tower needs to be placed
	* @param y				The y-index where the tower needs to be placed
	*/
	bool canBePlaced(uint8_t x, uint8_t y);
	/**
	* @brief Places towers on the target grid location
	* @param x				The x-index where the tower needs to be placed
	* @param y				The y-index where the tower needs to be placed
	* @param towerType		The type of tower that needs to be placed
	*/
	void placeTower(uint8_t x, uint8_t y, TowerType towerType);

	/**
	* @brief Clears all the towers from the grid
	*/
	void clearGrid();
};
