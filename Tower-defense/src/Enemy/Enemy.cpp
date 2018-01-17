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
	body.setRadius(20);
	body.setOrigin(sf::Vector2f(body.getRadius(), body.getRadius()));
	body.setPosition(sf::Vector2f(0.0, 0.0));
}

void Enemy::render()
{
	window.draw(body);
}

sf::Vector2f Enemy::getPosition()
{
	return body.getPosition();
}

void Enemy::decreaseHp(int dmg)
{
	hp -= dmg;
	if (hp <= 0)
	{
		dead = true;
	}
}

int Enemy::getGold()
{
	return gold;
}

sf::FloatRect Enemy::getBounds()
{
	return body.getGlobalBounds();
}

bool Enemy::isDead()
{
	return dead;
}

Enemy::~Enemy()
{
}
