#pragma once
#include "Enemy.h"
#include <math.h>

class EnemyGround : public Enemy
{
private:
	int target_counter;
public:
	EnemyGround(sf::RenderWindow& window, Grid& grid);
	~EnemyGround();

	void update() override;
	void move();
};

