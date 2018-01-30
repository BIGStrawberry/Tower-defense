#include "Enemy.h"


Enemy::Enemy(sf::RenderWindow& window, const std::vector<sf::Vector2f>& path, EnemyType type, uint16_t waveNumber) :
	window(window),
	path(path),
	next_target_pos(path[0]),
	distance(0.0),
	data(EnemyDataContainer::get(type)),
	slowed(false),
	original_speed(data.speed),
	bar(data.hp + (waveNumber * 2.5f))
{
	data.hp += waveNumber * 2.5f;
	data.gold += waveNumber;
	data.body.setPosition(path[0]);
	data.body.setRotation(-90.f);
}

void Enemy::render() const
{
	window.draw(data.body);
	bar.render(window);
}

const sf::Vector2f Enemy::getPosition() const
{
	return data.body.getPosition();
}

void Enemy::decreaseHp(float dmg)
{
	data.hp -= dmg;
	if (data.hp <= 0)
	{
		state = States::Dead;
	}
	bar.setHp(data.hp);
}

const int Enemy::getDmg() const
{
	return data.damage;
}

const int Enemy::getGold() const
{
	return data.gold;
}

sf::FloatRect Enemy::getBounds() const
{
	return data.body.getGlobalBounds();
}

Enemy::~Enemy()
{
}

void Enemy::reduce_speed(float factor, sf::Time time) {
	data.speed = original_speed;
	data.speed *= factor;
	slow_duration = time;
	slow_timer.restart();
	slowed = true;
}


bool Enemy::isSlowed()
{
	return slowed;
}