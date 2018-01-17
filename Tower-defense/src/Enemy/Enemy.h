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
	/// \param sf::RenderWindow& - Window to be rendered on.
	/// \param Grid& - Grid, should contain a public std::vector of coordinates of path.

#pragma endregion
	void decreaseHp(int dmg);
	sf::Vector2f getPosition();
	void render();
	virtual void update() = 0;
	int getGold();
	sf::FloatRect getBounds();
	bool isDead();
};