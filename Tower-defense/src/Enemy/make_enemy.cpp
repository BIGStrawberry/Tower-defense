#include "make_enemy.h"

std::shared_ptr<Enemy> make_enemy(EnemyType type, sf::RenderWindow& window, std::vector<sf::Vector2f>& path, uint16_t waveNumber)
{
	if (type == EnemyType::Flying || type == EnemyType::Boss_Flying)
	{
		return std::make_shared<EnemyAir>(window, path, type, waveNumber);
	}
	else
	{
		return std::make_shared<EnemyGround>(window, path, type, waveNumber);
	}
	return std::shared_ptr<Enemy>(nullptr);
}