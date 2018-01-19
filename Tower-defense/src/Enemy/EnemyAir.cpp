#include "EnemyAir.h"



EnemyAir::EnemyAir(sf::RenderWindow& window, const std::vector<sf::Vector2f> path, EnemyType type):
	Enemy(window, path, type)
{
	next_target_pos = *(path.end() - 1);
	distance = sqrt(pow(body.getPosition().x - next_target_pos.x, 2) + pow(body.getPosition().y - next_target_pos.y, 2));
	vector = (next_target_pos - body.getPosition()) / distance;
	body.setFillColor(sf::Color::Green);
}


EnemyAir::~EnemyAir()
{
}

void EnemyAir::update()
{
	if (speed > distance)
	{
		body.setPosition(next_target_pos);
		//deal dmg
		dead = true;
		gold = 0;
	}
	else
	{
		body.setPosition(body.getPosition() + (vector * speed));
		distance -= speed;
	}
	
}