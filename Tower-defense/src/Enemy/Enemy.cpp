#include "Enemy.h"


Enemy::Enemy(sf::RenderWindow& window, Grid& grid, EnemyType type) :
	window(window),
	grid(grid),
	next_target_pos(grid.path[0]),
	distance(0.0),
	speed(EnemyDataContainer::get(type).speed),
	hp(EnemyDataContainer::get(type).hp),
	dmg(EnemyDataContainer::get(type).damage),
	gold(EnemyDataContainer::get(type).gold)
{
	circle.setRadius(20);
	circle.setOrigin(sf::Vector2f(circle.getRadius(), circle.getRadius()));
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
