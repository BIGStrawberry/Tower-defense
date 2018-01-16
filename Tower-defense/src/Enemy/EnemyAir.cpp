#include "EnemyAir.h"



EnemyAir::EnemyAir(sf::RenderWindow& window, Grid& grid, EnemyType type):
	Enemy(window, grid, type)
{
	next_target_pos = *(grid.path.end() - 1);
	distance = sqrt(pow(circle.getPosition().x - next_target_pos.x, 2) + pow(circle.getPosition().y - next_target_pos.y, 2));
	vector = (next_target_pos - circle.getPosition()) / distance;
	circle.setFillColor(sf::Color::Green);
}


EnemyAir::~EnemyAir()
{
}

void EnemyAir::update()
{
	if (speed > distance)
	{
		circle.setPosition(next_target_pos);
	}
	else
	{
		circle.setPosition(circle.getPosition() + (vector * speed));
		distance -= speed;
	}
	
}