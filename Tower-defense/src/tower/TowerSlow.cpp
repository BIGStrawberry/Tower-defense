#include "TowerSlow.h"



TowerSlow::TowerSlow(sf::RenderWindow & window, float size, sf::Vector2f pos, std::vector<std::shared_ptr<Enemy>>& enemies, TowerType type, sf::Time slow_time, float slow_factor):
	Tower(window, size, pos, enemies, type),
	slow_time(slow_time),
	slow_factor(slow_factor)
{}


void TowerSlow::shootProjectile() {
	projectiles.push_back(std::make_unique<ProjectileSlow>(window, towerData.damage, tower_shape.getPosition(), target, slow_time, slow_factor));
}