#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <math.h>
#include <memory>
#include "Projectile.h"


class Tower
{
private:
	int range_radius;
	int turret_length;
	//Enemy* target;
	int cool_down;
	int cool_down_counter;
	bool render_range;
	std::vector<std::unique_ptr<Projectile>> projectiles;
	sf::RenderWindow & window;
	sf::CircleShape range_circle;
	sf::RectangleShape tower_shape;
	sf::VertexArray turret;
public:
	Tower(sf::RenderWindow & window, float size, sf::Vector2f position);
	void render();
	void update();
	~Tower();
};

