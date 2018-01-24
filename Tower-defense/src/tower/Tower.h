#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <math.h>
#include <memory>
#include <SFML/System.hpp>
#include "Projectile.h"
#include "../Enemy/make_enemy.h"
#include "TowerType.h"
#include "TowerDataContainer.h"
#include "TowerData.h"

/**
* @class Tower
* @file Tower.cpp
* @brief Class for a Tower
* 
* @details
* A tower is an object that has an Enemy target which it can shoot projectiles at.
* Everytime the update() is called, it will look for a target or check if the current one is still in range.
* The tower will create one projectile if the ready_to_fire bool is true. 
* The boolean ready_to_fire will be reset after reload_time (in seconds).
* It has a range circle which can be drawn around the tower when the render_range boolean is true.
* The tower will search for enemies in order of distance from the base.

* A tower will be given a TowerType, with which it can get the necessary TowerData for that type from the static TowerDataContainer.

* It can be updated and rendered.
*/
class Tower
{
protected:
	/**
	* @brief tower data
	*/
	TowerData towerData;
	/**
	* turret_lenght in pixels
	*/
	int turret_length;

	/**
	* bool to render the circle that displays the range of the tower
	*/
	bool render_range;


	/**
	* pointer to an enemy, set to nullptr when there is no enemy in range.
	*/
	std::shared_ptr<Enemy> target;

	/**
	* reference for vector of the enemies, used to choose a new target from.
	*/
	std::vector<std::shared_ptr<Enemy>>& enemies;
	/**
	* clock used to determine the time that has passed for reload.
	*/
	sf::Clock cooldown_timer;
	/**
	* projectile vector used to store the projectiles, and to update and render them.
	*/
	std::vector<Projectile> projectiles;

	/**
	* SFML window to draw on
	*/
	sf::RenderWindow & window;

	/**
	* circle shape used to display the range of the tower
	*/
	sf::CircleShape range_circle;
	/**
	* body of the tower
	*/
	sf::RectangleShape tower_shape;
	/**
	* VertexArray Linestrip used to draw the turret.
	*/
	sf::VertexArray turret;
	/**
	* @brief type of tower
	*/
	TowerType type;

	/**
	* @brief returns the distance to the Enemy using pythagoras theorem
	*/

	float getDistanceToEnemy(Enemy & rhs) const;

	/**
	* @brief caluclates the endpoint of the turret and sets the second vertex to that point.]
	*/

	void rotateTurret();

	/**
	* @brief returns the closest enemy in the radius, wrapped in shared_ptr. 
	Returns a shared_ptr with a nullptr when there is no enemy in the range.
	*/

	std::shared_ptr<Enemy> getClosestEnemyInRange() const;

	/**
	* @brief updates the projectiles in the projectile vector, removing them if they are not alive
	*/

	void update_projectiles();


	/**
	* @brief virtual method shootProjectiles
	Creates and stores a projectile in the projectiles container.
	This method is virtual so that Towers that inherit from Tower can create a different type of projectile and store it.
	*/
	virtual void shootProjectile();


public:
	/**
	* @brief 
	constructs the Tower 
	constructs the turret sets the first vertex point and the second, color.
	constructs the circle, sets the radius, origin and size.
	*/
	Tower(sf::RenderWindow & window, float size, sf::Vector2f pos, std::vector<std::shared_ptr<Enemy>>& enemies, TowerType type);

	/**
	* @brief setter for position
	* 
	*/
	void setPosition(const sf::Vector2f& pos) {
		tower_shape.setPosition(pos);
		range_circle.setPosition(tower_shape.getPosition());
	}

	/**
	* @brief setter for color
	*
	*/
	void setColor(const sf::Color& color) {
		tower_shape.setFillColor(color);
	}

	/**
	* @brief getter for towertype
	*/
	TowerType getType() {
		return type;
	}

	/**
	* @brief getter for tower cost
	*/
	int32_t getCost() const {
		return towerData.cost;
	}

	/**
	* @brief renders the Tower, projectiles, turret and range_circle if boolean render_range is true
	*/
	void render() const;

	/**
	* @brief rotates the turret, updates projectiles and updates the target pointer.
	Removes dead projectiles.
	Checks if enemy is out of range and searches for a new one.
	Creates a projectile after the reload_time if the tower has a target.
	
	*/
	void update();

};

