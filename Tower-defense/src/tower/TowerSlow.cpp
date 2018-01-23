#include "TowerSlow.h"



TowerSlow::TowerSlow(sf::RenderWindow & window, float size, sf::Vector2f pos, std::vector<std::shared_ptr<Enemy>>& enemies, TowerType type):
	Tower(window, size, pos, enemies, type)
{}


void TowerSlow::shootProjectile() {
	//projectiles.push_back(ProjectileSlow(window, 1, tower_shape.getPosition(), target));
}