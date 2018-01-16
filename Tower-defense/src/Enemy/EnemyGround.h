#pragma once
#include "Enemy.h"
#include <math.h>

class EnemyGround : public Enemy
{
public:
	EnemyGround(sf::RenderWindow& window, Grid& grid);
	~EnemyGround();

	void update() override;
	void move();
};

