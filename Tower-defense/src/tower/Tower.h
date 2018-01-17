#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <math.h>
#include <memory>
#include <SFML/System.hpp>
#include "Projectile.h"
#include "../Enemy/make_enemy.h"

class Tower
{
private:
	int radius;
	int turret_length;
	bool render_range;
	bool ready_to_fire;

	std::shared_ptr<Enemy> target;

	Grid & grid;
	sf::Clock cooldown_timer;
	std::vector<std::unique_ptr<Projectile>> projectiles;

	sf::RenderWindow & window;
	sf::CircleShape range_circle;
	sf::RectangleShape tower_shape;
	sf::VertexArray turret;

	float getDistanceToEnemy(Enemy & rhs);
	void rotateTurret();
	std::shared_ptr<Enemy> getClosestEnemyInRange();
	void update_projectiles();

public:
	Tower(sf::RenderWindow & window, float size, sf::Vector2f pos, int radius, Grid& grid);
	void render();
	void update();
	~Tower();
};

