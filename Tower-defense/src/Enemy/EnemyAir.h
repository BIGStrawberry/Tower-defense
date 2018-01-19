#pragma once
#include "Enemy.h"
#include <iostream>

#pragma region comment
/**
* @class EnemyAir
* @file EnemyAir.cpp
* @brief Class for EnemyAir units
* @details This is a concrete class, derived from class Enemy.
* Instances of this class will follow a straight line to the
* last coordinate in path (the base).
*/
#pragma endregion
class EnemyAir : public Enemy
{
public:
#pragma region comment
	/**
	* @brief EnemyAir Constructor
	* @param sf::RenderWindow&			window: SFML window instance to be rendered on.
	* @param std::vector<sf::Vector2f>&	path: Vector reference, which contains (at least 1) coordinate point(s).
	*									The enemy will follow the given path, until it reaches the base (last coordinate).
	* @param EnemyType					Type of the Enemy.
	*/

#pragma endregion
	EnemyAir(sf::RenderWindow& window, const std::vector<sf::Vector2f> path, EnemyType type);
	~EnemyAir();

#pragma region comment
	/**
	* @brief updates the object
	* @details This function will let the object move to the base.
	* If the object is marked as dead, the position won't change.
	*/

#pragma endregion
	void update() override;
};

