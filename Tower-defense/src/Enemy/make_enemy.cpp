#include "make_enemy.h"

std::shared_ptr<Enemy> make_enemy(EnemyType type, sf::RenderWindow& window, std::vector<sf::Vector2f>& path)
{
	Enemy* p = nullptr;
	if (type == EnemyType::Flying)
	{
		p = new EnemyAir(window, path, type);
	}
	else
	{
		p = new EnemyGround(window, path, type);
	}
	return std::shared_ptr<Enemy>(p);
}