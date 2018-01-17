#include "Tower.h"



Tower::Tower(sf::RenderWindow & window, float size, sf::Vector2f pos, int radius,  Grid& grid):
	radius(radius),
	turret_length(10),
	target(std::shared_ptr<Enemy>(nullptr)),
	grid(grid),
	render_range(true),
	ready_to_fire(true),
	window(window),
	range_circle(static_cast<float>(radius)),
	tower_shape(sf::Vector2f(size, size)),
	turret(sf::VertexArray(sf::LinesStrip, 2))

{

	turret[0].position = pos;
	turret[0].color = sf::Color::Black;
	turret[1].color = sf::Color::Black;
	turret[1].position = pos;
	tower_shape.setOrigin(sf::Vector2f(size/2, size/2));
	range_circle.setOrigin(sf::Vector2f(static_cast<float>(radius), static_cast<float>(radius)));
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


void Tower::rotateTurret() {
	sf::Vector2f diff = tower_shape.getPosition() - target->getPosition();
	float scale = getDistanceToEnemy(*target.get()) / turret_length;
	turret[1].position = tower_shape.getPosition() - sf::Vector2f(diff.x / scale, diff.y / scale);
}

std::shared_ptr<Enemy> Tower::getClosestEnemyInRange() {
	for (auto& enemy : grid.enemies) {
		if (getDistanceToEnemy(*enemy.get()) < radius) {
			return enemy;
		}
	}
	return std::shared_ptr<Enemy>(nullptr); //if no one found, return nullptr
}

void Tower::update_projectiles() {
	for (unsigned int i = 0; i < projectiles.size(); ++i) {
		if (projectiles[i]->isAlive()) {
			projectiles[i]->update();
		} else {
			projectiles.erase(projectiles.begin() + i);
			i--;
		}
	}
}

void Tower::update() {
	if (target.get() != nullptr) {
		rotateTurret();
		if (getDistanceToEnemy(*target.get()) > radius) { //if target is out of range
			target = getClosestEnemyInRange(); // find new one
		}
		if (target.get() != nullptr){
			if (target->isDead()) {
				projectiles.clear();
			}
		}
		if (ready_to_fire) {
			projectiles.push_back(std::make_unique<Projectile>(window, 21, tower_shape.getPosition(), target));
			cooldown_timer.restart();
			ready_to_fire = false;
		}
		else if (cooldown_timer.getElapsedTime().asSeconds() > 1){ //check timer
			ready_to_fire = true;
		}

	}
	else {
		target = getClosestEnemyInRange(); // find new enemy
	}
	update_projectiles();

}

//void Tower::update() {
//	if (target.get() != nullptr && target->isDead()) {
//		target = std::shared_ptr<Enemy>(nullptr);
//		projectiles.clear();
//	}
//	
//
//	float distance_to_target;
//	sf::Vector2f mypos = tower_shape.getPosition(), diff;
//	if (target.get() == nullptr) {
//		for (auto& enemy : grid.enemies) {
//			distance_to_target = getDistanceToEnemy(*enemy.get());
//			if (distance_to_target < radius) {
//				target = enemy;
//				break;
//			}
//		}
//	}
//	else {
//		distance_to_target = getDistanceToEnemy(*target.get());
//		if (distance_to_target > radius) { // find new enemy
//			target = std::shared_ptr<Enemy>(nullptr);
//			for (auto& enemy : grid.enemies) {
//				distance_to_target = getDistanceToEnemy(*enemy.get());
//				if (distance_to_target < radius) {
//					target = enemy;
//					break;
//				}
//			}
//		}
//	}
//	if (!ready_to_fire) {
//		if (cooldown_timer.getElapsedTime().asSeconds() > 1){
//		ready_to_fire = true;
//		}
//	}
//	else {
//		if (target.get() != nullptr) {
//			projectiles.push_back(std::make_unique<Projectile>(window, 10, tower_shape.getPosition(), target));
//			cooldown_timer.restart();
//			ready_to_fire = false;
//		}
//	}
//
//	if (target.get() != nullptr) {
//		diff = tower_shape.getPosition() - target->getPosition();
//		float scale = distance_to_target / turret_length;
//		turret[1].position = mypos - sf::Vector2f(diff.x / scale, diff.y / scale);
//	}
//	for (unsigned int i = 0; i < projectiles.size(); ++i) {
//		if (projectiles[i]->isAlive()) {
//			projectiles[i]->update();
//		} else {
//			projectiles.erase(projectiles.begin() + i);
//			i--;
//		}
//	}
//}
