#pragma once
#include "Enemy.h"
#include <math.h>

class EnemyGround : public Enemy
{
private:
	unsigned int target_counter;
public:
	EnemyGround(sf::RenderWindow& window, Grid& grid, EnemyType type);
	~EnemyGround();

	void update() override;
	void move();
};

