#pragma once
#include "Projectile.h"
#include <SFML/Graphics.hpp>

/**
* @class ProjectileSlow
* @file ProjectileSlow.cpp
@brief This Projectile behaves the same as a regular Projectile except that it calls reduceSpeed on impact with the target.
*

*/


class ProjectileSlow: public Projectile {
private:

	/*
	Reference to the Factor with which the speed is reduced.
	Should be between 0 and 1.
	*/
	float& slow_factor;

	/*
	duration that the target is slowed in sf::Time.
	*/
	sf::Time& slow_time;
	
	/*
	Called when projectileslow and target overlap.
	It is overriden because it also calls reduceSpeed on the target.
	*/

	void onImpact() override;
public:
	ProjectileSlow(sf::RenderWindow & window, int damage, sf::Vector2f position, std::shared_ptr<Enemy> & target, sf::Time& slow_time, float& slow_factor);
};

