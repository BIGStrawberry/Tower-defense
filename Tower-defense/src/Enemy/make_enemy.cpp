#include "make_enemy.h"

std::shared_ptr<Enemy> make_enemy(EnemyType type, sf::RenderWindow& window, Grid& grid)
{
	Enemy* p = nullptr;
	if (type == EnemyType::Flying)
	{
		p = new EnemyAir(window, grid, type);
	}
	else
	{
		p = new EnemyGround(window, grid, type);
	}
	return std::shared_ptr<Enemy>(p);
}