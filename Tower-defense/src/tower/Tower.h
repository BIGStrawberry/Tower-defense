#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <math.h>
#include <memory>
#include <SFML/System.hpp>
#include "Projectile.h"
#include "../Enemy/make_enemy.h"
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

* It can be updated and rendered.
*/
class Tower
{
private:
	/**
	* radius in pixels
	*/
	int radius;
	/**
	* turret_lenght in pixels
	*/
	int turret_length;
	/**
	* time between each projectile in seconds
	*/
	int reload_time;

	/**
	* bool to render the circle that displays the range of the tower
	*/
	bool render_range;
	/**
	* bool used for rate of fire
	*/
	bool ready_to_fire;


	/**
	* pointer to an enemy, set to nullptr when there is no enemy in range.
	*/
	std::shared_ptr<Enemy> target;

	/**
	* Grid reference for list of the enemies.
	*/
	Grid & grid;
	/**
	* clock used to determine the time that has passed for reload.
	*/
	sf::Clock cooldown_timer;
	/**
	* projectile vector used to store the projectiles, and to update and render them.
	*/
	std::vector<std::unique_ptr<Projectile>> projectiles;

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
	* @brief returns the distance to the Enemy using pythagoras theorem
	*/

	float getDistanceToEnemy(Enemy & rhs);

	/**
	* @brief caluclates the endpoint of the turret and sets the second vertex to that point.]
	*/

	void rotateTurret();

	/**
	* @brief returns the closest enemy in the radius, wrapped in shared_ptr. 
	Returns a shared_ptr with a nullptr when there is no enemy in the range.
	*/

	std::shared_ptr<Enemy> getClosestEnemyInRange();

	/**
	* @brief updates the projectiles in the projectile vector, removing them if they are not alive
	*/

	void update_projectiles();

public:
	/**
	* @brief 
	constructs the Tower 
	constructs the turret sets the first vertex point and the second, color.
	constructs the circle, sets the radius, origin and size.
	*/
	Tower(sf::RenderWindow & window, float size, sf::Vector2f pos, int radius, Grid& grid, int fire_rate);

	/**
	* @brief renders the Tower, projectiles, turret and range_circle if boolean render_range is true
	*/
	void render();

	/**
	* @brief rotates the turret, updates projectiles and updates the target pointer.
	Removes dead projectiles.
	Checks if enemy is out of range and searches for a new one.
	Creates a projectile after the reload_time if the tower has a target.
	
	*/
	void update();

};

