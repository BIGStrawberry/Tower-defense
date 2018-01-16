#pragma once
#include "Enemy.h"
#include <iostream>

class EnemyAir : public Enemy
{
public:
	EnemyAir(sf::RenderWindow& window, Grid& grid);
	~EnemyAir();

	void update() override;
};

