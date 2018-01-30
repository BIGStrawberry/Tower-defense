#include "EnemyGround.h"
#include <iostream>



EnemyGround::EnemyGround(sf::RenderWindow& window, const std::vector<sf::Vector2f>& path, EnemyType type, uint16_t waveNumber):
	Enemy(window, path, type, waveNumber),
	target_counter(0)
{
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

		if (path.size() > target_counter)
		{
			next_target_pos = path[target_counter];
			distance = sqrt(pow(pos.x - next_target_pos.x, 2) + pow(pos.y - next_target_pos.y, 2));
			sf::Vector2f diff = next_target_pos - body.getPosition();
			float angle_rads = std::atan2(diff.y, diff.x); // calculate angle for rotation.
			float degrees = angle_rads * (180 / 3.141592f);
			body.setRotation(degrees - 90);
			vector = diff / distance;
			target_counter++;
		}
		else
		{
			state = States::Reached_Base;
			return;
		}

	}
	move();

	if (slowed) {
		if (slow_timer.getElapsedTime() >= slow_duration) {
			slowed = false;
			speed = original_speed;
		}
	}
	bar.setPosition(body.getPosition());
}