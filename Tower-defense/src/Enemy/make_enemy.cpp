#include "make_enemy.h"

std::shared_ptr<Enemy> make_enemy(EnemyType type, sf::RenderWindow& window, std::vector<sf::Vector2f>& path)
{
	if (type == EnemyType::Flying)
	{
		return std::make_shared<EnemyAir>(window, path, type);
	}
	else
	{
		return std::make_shared<EnemyGround>(window, path, type);
	}
	return std::shared_ptr<Enemy>(nullptr);
}