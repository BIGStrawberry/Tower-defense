#include "Tower.h"
#include <iostream>



Tower::Tower(sf::RenderWindow & window, float size, sf::Vector2f pos, std::vector<std::shared_ptr<Enemy>>& enemies, TowerType type):
	towerData(TowerDataContainer::get(type)),
	turret_length(10),
	target(std::shared_ptr<Enemy>(nullptr)),
	enemies(enemies),
	render_range(false),
	window(window),
	turret(towerData.turret_sprites[0]),
	type(type),
	range_circle(towerData.radius),
	upgrade_level(0),
	upgrade_cost(towerData.cost),
	acculumated_cost(towerData.cost)
{
	tower_shape.setTexture(TextureContainer::get("base.png"));
	turret.setPosition(pos);
	tower_shape.setScale(0.3f, 0.3f);
	tower_shape.setOrigin(64.f, 64.f);
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
	if (render_range) {
		window.draw(range_circle);
	}

	for (const auto& pt : projectiles) {
		pt->render();
	}
	window.draw(turret);
}


void Tower::rotateTurret() {
	sf::Vector2f diff = target->getPosition() - tower_shape.getPosition();
	float angle_rads = std::atan2(diff.y, diff.x);
	float degrees = angle_rads * (180 / 3.141592f);
	turret.setRotation(degrees+180);

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
	auto pos = turret.getPosition();
	turret = towerData.turret_sprites[upgrade_level];
	turret.setPosition(pos);
	// Give tower damage a multiplier based on the upgrade level
	towerData.damage *= static_cast<float>(upgrade_level * 1.1);

	// Add the cost of this upgrade to the total amount of gold the tower has cost
	acculumated_cost += upgrade_cost;

	// The upgrade cost becomes more based on the level of upgrades you have
	upgrade_cost = static_cast<uint32_t>(towerData.cost * (upgrade_level * 1.1));

	// Give the tower radius a multiplier
	towerData.radius *= static_cast<float>(1.2);

	range_circle.setRadius(towerData.radius); 
	range_circle.setOrigin(sf::Vector2f(towerData.radius, towerData.radius));

	std::cout << "upgraded to level " << static_cast<int>(upgrade_level) << "\n";
}

uint8_t Tower::getUpgradeLevel() {
	return upgrade_level;
}
