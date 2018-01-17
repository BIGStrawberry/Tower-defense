#include "Enemy.h"


Enemy::Enemy(sf::RenderWindow& window, const std::vector<sf::Vector2f>& path, EnemyType type) :
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

void Enemy::render() const
{
	if (!dead)
	{
		window.draw(body);
	}
}

const sf::Vector2f Enemy::getPosition() const
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

const int Enemy::getGold() const
{
	return gold;
}

sf::FloatRect Enemy::getBounds() const
{
	return body.getGlobalBounds();
}

const bool Enemy::isDead() const
{
	return dead;
}

Enemy::~Enemy()
{
}
