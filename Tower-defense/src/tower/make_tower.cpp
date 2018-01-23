#include "make_tower.h"



std::shared_ptr<Tower> make_tower(sf::RenderWindow & window, float size, sf::Vector2f pos, std::vector<std::shared_ptr<Enemy>>& enemies, TowerType type) {
	if (type == TowerType::Normal || type == TowerType::Long) {
		return std::make_shared<Tower>(window, size, pos, enemies, type);
	}
	else if (type == TowerType::Slow){
		return std::make_shared<TowerSlow>(window, size, pos, enemies, type);
	}
	else {
		return std::shared_ptr<Tower> (nullptr);
	}
}
