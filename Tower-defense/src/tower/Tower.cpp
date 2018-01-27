#include "Tower.h"
#include <iostream>



Tower::Tower(sf::RenderWindow & window, float size, sf::Vector2f pos, std::vector<std::shared_ptr<Enemy>>& enemies, TowerType type):
	towerData(TowerDataContainer::get(type)),
	turret_length(10),
	target(std::shared_ptr<Enemy>(nullptr)),
	enemies(enemies),
	render_range(false),
	window(window),
	tower_shape(sf::Vector2f(size, size)),
	turret(sf::VertexArray(sf::LinesStrip, 2)),
	type(type),
	range_circle(towerData.radius),
	upgrade_level(0),
	upgrade_cost(towerData.cost),
	acculumated_cost(towerData.cost)
{
	turret[0].position = pos;
	turret[0].color = sf::Color::Black;
	turret[1].color = sf::Color::Black;
	turret[1].position = pos;
	tower_shape.setOrigin(sf::Vector2f(size/2, size/2));
	range_circle.setOrigin(sf::Vector2f(towerData.radius, towerData.radius));
	range_circle.setFillColor(sf::Color::Transparent);
	range_circle.setOutlineColor(sf::Color::Black);
	range_circle.setOutlineThickness(1.0);

	tower_shape.setPosition(pos);
	range_circle.setPosition(pos);
}


float Tower::getDistanceToEnemy(Enemy & rhs) const {
	sf::Vector2f diff = tower_shape.getPosition() - rhs.getPosition();
	return std::sqrt(std::pow(diff.x, 2.0f) + std::pow(diff.y, 2.0f));
}

void Tower::render() const {
	window.draw(tower_shape);
	window.draw(turret);
	if (render_range) {
		window.draw(range_circle);
	}

	for (const auto& pt : projectiles) {
		pt->render();
	}
}


void Tower::rotateTurret() {
	sf::Vector2f diff = tower_shape.getPosition() - target->getPosition();
	float scale = getDistanceToEnemy(*target.get()) / turret_length;
	turret[1].position = tower_shape.getPosition() - sf::Vector2f(diff.x / scale, diff.y / scale);
}

std::shared_ptr<Enemy> Tower::getClosestEnemyInRange() const {
	for (const auto& enemy : enemies) {
		if (getDistanceToEnemy(*enemy.get()) < towerData.radius) {
			return enemy;
		}
	}
	return std::shared_ptr<Enemy>(nullptr); //if none found, return nullptr
}

void Tower::update_projectiles() {
	for (unsigned int i = 0; i < projectiles.size(); ++i) {
		if (!projectiles[i]->isDead()) {
			projectiles[i]->update();
		} else {
			projectiles.erase(projectiles.begin() + i);
			i--;
		}
	}
}

sf::FloatRect Tower::getBounds()
{
	return tower_shape.getGlobalBounds();
}

sf::Vector2f Tower::getPosition()
{
	return tower_shape.getPosition();
}

void Tower::enableRangeRender(bool s)
{
	render_range = s;
}


void Tower::shootProjectile() {

	projectiles.push_back(std::make_unique<Projectile>(window, towerData.damage, tower_shape.getPosition(), target));
}

void Tower::update() {
	if (target != nullptr && target->state == Enemy::States::Walking) {
		rotateTurret();
		if (cooldown_timer.getElapsedTime() > towerData.reload_time) {
			shootProjectile();
			cooldown_timer.restart();
		}
		if (getDistanceToEnemy(*target.get()) > towerData.radius) { //if target is out of range
			target = getClosestEnemyInRange(); // find new one
		}
	}
	else {
		target = getClosestEnemyInRange(); // find new enemy
	}
	update_projectiles();

}


void Tower::upgrade() {
	upgrade_level++;
	towerData.damage *= 1.25;
	acculumated_cost += upgrade_cost;
	upgrade_cost *= 2;
	towerData.radius *= 1.5;
	range_circle.setRadius(towerData.radius); 
	range_circle.setOrigin(sf::Vector2f(towerData.radius, towerData.radius));
	std::cout << "upgraded to level " << static_cast<int>(upgrade_level) << "\n";
	
}

uint8_t Tower::getUpgradeLevel() {
	return upgrade_level;
}
