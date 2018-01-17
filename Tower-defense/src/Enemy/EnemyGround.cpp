#include "EnemyGround.h"
#include <iostream>



EnemyGround::EnemyGround(sf::RenderWindow& window, Grid& grid, EnemyType type):
	Enemy(window, grid, type),
	target_counter(0)
{
	body.setFillColor(sf::Color::Red);
}


EnemyGround::~EnemyGround()
{
}

void EnemyGround::move()
{
	if (speed > distance)
	{
		body.setPosition(next_target_pos);
		distance = 0;

	}
	else
	{
		body.setPosition(body.getPosition() + (vector * speed));
		distance -= speed;
	}
}


void EnemyGround::update()
{
	if (distance == 0)
	{
		sf::Vector2f pos = body.getPosition();
		
		if (grid.path.size() > target_counter)
		{
			next_target_pos = grid.path[target_counter];
			distance = sqrt(pow(pos.x - next_target_pos.x, 2) + pow(pos.y - next_target_pos.y, 2));
			vector = (next_target_pos - body.getPosition()) / distance;
			target_counter++;
		}
		else
		{
			//deal dmg
			dead = true;
			gold = 0;
			return;
		}
		
	}
	move();
}