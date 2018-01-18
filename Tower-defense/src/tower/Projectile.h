#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <memory>
#include "../Enemy/Enemy.h"


/**
* @class Projectile
* @file Projectile.cpp
* @brief A projectile is an object created by a Tower that will follow its target and damage it.
*
* @details
* A projectile has a target Enemy given in the constructor which it will follow.
* Once it overlaps with the Enemy target, it will deal damage.
* If the Enemy is destroyed before the projectile can reach it, the projectile will set is_alive to false and will be removed by it's parent.

*/

class Projectile {
private:
	/**
	* this is the number of pixels the projectile jumps each update.
	*/
	float speed;
	/**
	* Amount that will be substracted from the enemy when it overlaps
	*/
	int damage;
	/**
	* bool to notify parent it should be removed.
	*/
	bool is_dead;
	/**
	* shape used to display the projectile
	*/
	sf::CircleShape body;
	/**
	SFML window to draw on
	*/
	sf::RenderWindow * window;
	/**
	The enemy it is tracking and will deal damage to.
	*/
	std::shared_ptr<Enemy> target;
public:
	/**
	@brief constructs the projectile, sets color, origin and position.
	*/
	Projectile(sf::RenderWindow & window, int damage, sf::Vector2f position, std::shared_ptr<Enemy> & target);
	/**
	* @brief renders the body
	*/
	void render() const;
	/**
	* @brief checks if the target is still alive, checks if it overlaps with enemy (deals damage) and calculates next jump using pythagoras theorem.
	*/
	void update();
	/**
	* @brief returns wether projectile is still alive.
	*/
	bool isDead();

	

};

