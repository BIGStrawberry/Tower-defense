#include "Tower.h"



Tower::Tower(sf::RenderWindow & window, float size, sf::Vector2f pos, Grid& grid):
	range_radius(400),
	turret_length(10),
	target(std::shared_ptr<Enemy>(nullptr)),
	grid(grid),
	render_range(true),
	window(window),
	range_circle(static_cast<float>(range_radius)),
	tower_shape(sf::Vector2f(size, size)),
	turret(sf::VertexArray(sf::LinesStrip, 2))

{

	turret[0].position = pos;
	turret[0].color = sf::Color::Black;
	turret[1].color = sf::Color::Black;
	turret[1].position = pos;
	tower_shape.setOrigin(sf::Vector2f(size/2, size/2));
	range_circle.setOrigin(sf::Vector2f(static_cast<float>(range_radius), static_cast<float>(range_radius)));
	range_circle.setFillColor(sf::Color::Transparent);
	range_circle.setOutlineColor(sf::Color::Black);
	range_circle.setOutlineThickness(1.0);

	tower_shape.setPosition(pos);
	range_circle.setPosition(pos);

}


Tower::~Tower()
{
}


float Tower::getDistanceToEnemy(Enemy & rhs) {
	sf::Vector2f diff = tower_shape.getPosition() - rhs.getPosition();
	return std::sqrt(std::pow(diff.x, 2.0f) + std::pow(diff.y, 2.0f));

}

void Tower::render() {
	window.draw(tower_shape);
	window.draw(turret);
	if (render_range) {
		window.draw(range_circle);
	}
	sf::Vector2f enemypos(1200, 700);
	sf::CircleShape temp(10.0);
	temp.setPosition(enemypos);
	window.draw(temp);

	for (auto& pt : projectiles) {
		pt->render();
	}
}



void Tower::update() {
	if (target.get() != nullptr && target->isDead()) {
		target = std::shared_ptr<Enemy>(nullptr);
		grid.enemies.clear(); 
		grid.enemies.push_back(make_enemy(EnemyType::Normal, window, grid));
		projectiles.clear();
	}
	

	float distance_to_target;
	sf::Vector2f mypos = tower_shape.getPosition(), diff;
	if (target.get() == nullptr) {
		for (auto& enemy : grid.enemies) {
			distance_to_target = getDistanceToEnemy(*enemy.get());
			if (distance_to_target < range_radius) {
				target = enemy;
				break;
			}
		}
	}
	else {
		distance_to_target = getDistanceToEnemy(*target.get());
		if (distance_to_target > range_radius) { // find new enemy
			for (auto& enemy : grid.enemies) {
				distance_to_target = getDistanceToEnemy(*enemy.get());
				if (distance_to_target < range_radius) {
					target = enemy;
					break;
				}
			}
		}
	}
	if (!ready_to_fire) {
		if (cooldown_timer.getElapsedTime().asSeconds() > 1){
		ready_to_fire = true;
		}
	}
	else {
		if (target.get() != nullptr) {
			projectiles.push_back(std::make_unique<Projectile>(window, 10, tower_shape.getPosition(), target));
			cooldown_timer.restart();
			ready_to_fire = false;
		}
	}

	if (target.get() != nullptr) {
		diff = tower_shape.getPosition() - target->getPosition();
		float scale = distance_to_target / turret_length;
		turret[1].position = mypos - sf::Vector2f(diff.x / scale, diff.y / scale);
		for (unsigned int i = 0; i < projectiles.size(); ++i) {
			if (projectiles[i]->isAlive()) {
				projectiles[i]->update();
			} else {
				projectiles.erase(projectiles.begin() + i);
				i--;
			}
		}
	}

}
