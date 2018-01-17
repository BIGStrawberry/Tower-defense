#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "EnemyType.h"
#include "EnemyDataContainer.h"

#pragma region comment
/// @file

/// \brief
/// class Grid
/// \details
/// Dummy class, used by Enemy.
#pragma endregion

class Grid
{
public:
	std::vector<sf::Vector2f> path;
};

#pragma region comment
/// \brief
/// class Enemy
/// \details
/// Abstract base class for enemy units.
#pragma endregion

class Enemy
{
protected:
	sf::RenderWindow& window;
	Grid& grid;
	float distance;
	sf::CircleShape body;
	sf::Vector2f next_target_pos;
	sf::Vector2f vector;
	float speed;
	int hp;
	int dmg;
	int gold;
	bool dead;

public:
#pragma region comment
	/// \brief
	///  constructor
	/// \param sf::RenderWindow& - Window to be rendered on.
	/// \param Grid& - Grid, should contain a public std::vector of coordinates of path.

#pragma endregion
	Enemy(sf::RenderWindow& window, Grid& grid, EnemyType type);
	~Enemy();

#pragma region comment
	/// \brief
	///  lowers hp of enemy
	/// \param int - damage
	/// \details
	/// This function will be called by a projectile object when overlap.

#pragma endregion
	void decreaseHp(int dmg);
#pragma region comment
	/// \brief
	///  gets position

#pragma endregion
	sf::Vector2f getPosition();
#pragma region comment
	/// \brief
	///  renders object

#pragma endregion
	void render();
#pragma region comment
	/// \brief
	///  updates the state of the object
	/// \details
	/// This function will be called once per update loop.

#pragma endregion
	virtual void update() = 0;
#pragma region comment
	/// \brief
	///  returns the amount of gold that the unit gives when killed.

#pragma endregion
	int getGold();
#pragma region comment
	/// \brief
	///  returns global bounds of object

#pragma endregion
	sf::FloatRect getBounds();
#pragma region comment
	/// \brief
	///  returns if unit is dead

#pragma endregion
	bool isDead();
};