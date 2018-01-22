#pragma once
#include "..\tower\Tower.h"

/**
* @class Tower
* @file Tower.cpp
  @brief This Tower behaves the same as a regular Tower except that it shoots a ProjectileSlow.
*
* @details
* This is a Tower that shoots a different projectile than the Tower it inherits from.
* This Tower overrides the shootProjectile method from Tower.
* Instead of creating and storing a regular Projectile, it will create a ProjectileSlow.

*/

class TowerSlow: public Tower {
private:
	void shootProjectile() override;
public:
	TowerSlow(sf::RenderWindow & window, float size, sf::Vector2f pos, std::vector<std::shared_ptr<Enemy>>& enemies, TowerType type);
	
};

