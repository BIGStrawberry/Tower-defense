#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>


class Projectile {
private:
	float speed;
	float damage;
	bool is_alive;
	sf::CircleShape body;
	sf::RenderWindow & window;
	//enemy target
public:
	Projectile(sf::RenderWindow & window, float damage, sf::Vector2f position);
	void render();
	void update();
	bool isAlive();

	~Projectile();
};

