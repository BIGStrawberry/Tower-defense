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
	int range_radius;
	int turret_length;
	std::shared_ptr<Enemy> target;
	Grid & grid;
	sf::Clock cooldown_timer;
	bool render_range;
	bool ready_to_fire = true;
	sf::Vector2f enemypos;
	std::vector<std::unique_ptr<Projectile>> projectiles;
	sf::RenderWindow & window;
	sf::CircleShape range_circle;
	sf::RectangleShape tower_shape;
	sf::VertexArray turret;

	float getDistanceToEnemy(Enemy & rhs);

public:
	Tower(sf::RenderWindow & window, float size, sf::Vector2f position, Grid& grid);
	void render();
	void update();
	~Tower();
};

