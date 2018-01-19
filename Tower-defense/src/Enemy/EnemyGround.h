#pragma once
#include "Enemy.h"

#pragma region comment
/**
* @class EnemyGround
* @file EnemyAir.cpp
* @brief Class for EnemyGround units
* @details This is a concrete class, derived from class Enemy.
* Instances of this class will follow a path.
*/
#pragma endregion
class EnemyGround : public Enemy
{
private:
	unsigned int target_counter;
	
	void move();
public:
#pragma region comment
	/**
	* @brief EnemyGround Constructor
	* @param sf::RenderWindow&			window: SFML window instance to be rendered on.
	* @param std::vector<sf::Vector2f>&	path: Vector reference, which contains (at least 1) coordinate point(s).
	*									The enemy will follow the given path, until it reaches the base (last coordinate).
	* @param EnemyType					Type of the Enemy.
	*/

#pragma endregion
	EnemyGround(sf::RenderWindow& window, const std::vector<sf::Vector2f> path, EnemyType type);
	~EnemyGround();
#pragma region comment
	/**
	* @brief updates the object
	* @details This function will let the object move in the direction of
	* the next coordinate on the path.
	* If the object is marked as dead, the position won't change.
	*/

#pragma endregion
	void update() override;
};
