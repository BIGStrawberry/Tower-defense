#include "TowerSlow.h"



TowerSlow::TowerSlow(sf::RenderWindow & window, float size, sf::Vector2f pos, std::vector<std::shared_ptr<Enemy>>& enemies, TowerType type, sf::Time slow_time, float slow_factor):
	Tower(window, size, pos, enemies, type),
	slow_time(slow_time),
	slow_factor(slow_factor)
{}


void TowerSlow::shootProjectile() {
	projectiles.push_back(std::make_unique<ProjectileSlow>(window, towerData.damage, tower_shape.getPosition(), target, slow_time, slow_factor));
}


std::shared_ptr<Enemy> TowerSlow::findNotSlowed()
{
	for (const auto& enemy : enemies) {
		if (getDistanceToEnemy(*enemy.get()) < towerData.radius && !enemy->isSlowed()) {
			return enemy;
		}
	}
	return std::shared_ptr<Enemy>(nullptr); //if none found, return nullptr
}


void TowerSlow::update()
{
	if (target != nullptr && target->state == Enemy::States::Walking) {
		rotateTurret();
		if (cooldown_timer.getElapsedTime() > towerData.reload_time) {
			shootProjectile();
			cooldown_timer.restart();
		}
	}
	if (!(target = findNotSlowed()))
	{
		target = getClosestEnemyInRange();
	}
	update_projectiles();
}