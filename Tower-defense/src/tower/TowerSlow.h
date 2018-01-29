#pragma once
#include "..\tower\Tower.h"
#include "..\tower\ProjectileSlow.h"


/**
* @class TowerSlow
* @file TowerSlow.cpp
  @brief This Tower behaves the same as a regular Tower except that it shoots a ProjectileSlow.
*
* @details
* This is a Tower that shoots a different projectile than the Tower it inherits from.
* This Tower overrides the shootProjectile method from Tower.
* Instead of creating and storing a regular Projectile, it will create a ProjectileSlow.

*/

class TowerSlow: public Tower {
private:
	/*
	Duration that the target is slowed in sf::Time.
	*/
	sf::Time slow_time;
	/*
	Factor with which the speed is reduced.
	Should be between 0 and 1.
	*/
	float slow_factor;
	/*
	overriden method that adds a projectileSlow to the projectiles vector.
	*/
	void shootProjectile() override;

	/**
	* @brief This function returns a pointer to the closest enemy,
	that is not currently being slowed. If there is no such enemy,
	the function will return nullptr.
	*/
	std::shared_ptr<Enemy> findNotSlowed();


public:
	TowerSlow(sf::RenderWindow & window, float size, sf::Vector2f pos, std::vector<std::shared_ptr<Enemy>>& enemies, TowerType type, sf::Time slow_time, float slow_factor);

	/**
	* @brief rotates the turret, updates projectiles and updates the target pointer.
	Removes dead projectiles.
	Checks if enemy is out of range and searches for a new one.
	Creates a projectile after the reload_time if the tower has a target.

	*/
	void update() override;
	
};

