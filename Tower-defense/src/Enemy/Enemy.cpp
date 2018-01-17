#include "Enemy.h"


Enemy::Enemy(sf::RenderWindow& window, std::vector<sf::Vector2f>& path, EnemyType type) :
	window(window),
	path(path),
	next_target_pos(path[0]),
	distance(0.0),
	speed(EnemyDataContainer::get(type).speed),
	hp(EnemyDataContainer::get(type).hp),
	dmg(EnemyDataContainer::get(type).damage),
	gold(EnemyDataContainer::get(type).gold)
{
	body.setRadius(20);
	body.setOrigin(sf::Vector2f(body.getRadius(), body.getRadius()));
	body.setPosition(path[0]);
}

void Enemy::render()
{
	if (!dead)
	{
		window.draw(body);
	}
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
