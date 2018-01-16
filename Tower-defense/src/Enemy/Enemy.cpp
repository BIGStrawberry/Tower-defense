#include "Enemy.h"


Enemy::Enemy(sf::RenderWindow& window, Grid& grid) :
	window(window),
	grid(grid),
	target_counter(0),
	next_target_pos(grid.path[0]),
	distance(0.0),
	speed(3)
{
	circle.setRadius(20);
	circle.setOrigin(sf::Vector2f(circle.getRadius(), circle.getRadius()));
	circle.setFillColor(sf::Color::Red);
	circle.setPosition(sf::Vector2f(0.0, 0.0));
}

void Enemy::render()
{
	window.draw(circle);
}

sf::Vector2f Enemy::getPosition()
{
	return circle.getPosition();
}

void Enemy::decreaseHp(int dmg)
{
	hp -= dmg;
	if (hp <= 0)
	{
		dead = true;
	}
}

Enemy::~Enemy()
{
}
