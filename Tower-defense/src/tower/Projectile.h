#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <memory>
#include "../Enemy/Enemy.h"


class Projectile {
private:
	float speed;
	int damage;
	bool is_alive;
	sf::CircleShape body;
	sf::RenderWindow & window;
	std::shared_ptr<Enemy> target;
public:
	Projectile(sf::RenderWindow & window, int damage, sf::Vector2f position, std::shared_ptr<Enemy> & target);
	void render();
	void update();
	bool isAlive();

	~Projectile();
};

