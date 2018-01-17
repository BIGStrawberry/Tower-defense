#pragma once
#include "Enemy.h"
#include <math.h>

class EnemyGround : public Enemy
{
private:
	unsigned int target_counter;
	
	void move();
public:
#pragma region comment
	/// \brief
	///  constructor
	/// \param sf::RenderWindow& - Window to be rendered on.
	/// \param Grid& - Grid, should contain a public std::vector of coordinates of path.
	/// \param EnemyType - type of unit

#pragma endregion
	EnemyGround(sf::RenderWindow& window, Grid& grid, EnemyType type);
	~EnemyGround();
#pragma region comment
	/// \brief
	///  updates the state of the object
	/// \details
	/// This function will be called once per update loop.

#pragma endregion
	void update() override;
};

