#include "EnemyGround.h"
#include <iostream>



EnemyGround::EnemyGround(sf::RenderWindow& window, Grid& grid):
	Enemy(window, grid)
{
}


EnemyGround::~EnemyGround()
{
}

void EnemyGround::move()
{
	if (speed > distance)
	{
		circle.setPosition(next_target_pos);
		distance = 0;

	}
	else
	{
		circle.setPosition(circle.getPosition() + (vector * speed));
		distance -= speed;
	}
}


void EnemyGround::update()
{
	if (distance == 0)
	{
		sf::Vector2f pos = circle.getPosition();
		target_counter++;
		if (grid.path.size() > target_counter)
		{
			next_target_pos = grid.path[target_counter];
			distance = sqrt(pow(pos.x - next_target_pos.x, 2) + pow(pos.y - next_target_pos.y, 2));
			vector = (next_target_pos - circle.getPosition()) / distance;
		}
		else
		{
			//deal dmg
			dead = true;
			return;
		}
		
	}
	move();
}