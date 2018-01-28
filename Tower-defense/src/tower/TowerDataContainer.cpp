#include "TowerDataContainer.h"
#include <iostream>


std::map<TowerType, TowerData> TowerDataContainer::container; 

TowerData& TowerDataContainer::get(TowerType type) {
	return container[type];
}



void TowerDataContainer::load() {
	sf::Sprite turret;
	turret.setOrigin(64.f, 64.f);
	turret.setTexture(TextureContainer::get("normal_turret.png"));
	turret.setScale(sf::Vector2f(0.27f, 0.27f));

	container.insert(std::pair<TowerType, TowerData>(TowerType::Normal, TowerData{75.0f, sf::milliseconds(500), 1, 75, turret}));

	turret.setOrigin(64.f, 64.f);
	turret.setTexture(TextureContainer::get("slow_turret.png"));
	turret.setScale(sf::Vector2f(0.27f, 0.27f));

	container.insert(std::pair<TowerType, TowerData>(TowerType::Slow, TowerData{75.0f, sf::milliseconds(500), 1, 75, turret}));

	turret.setOrigin(32.f, 37.f);
	turret.setTexture(TextureContainer::get("long_turret.png"));
	turret.setScale(sf::Vector2f(0.5f, 0.5f));

	container.insert(std::pair<TowerType, TowerData>(TowerType::Long, TowerData{125.0f, sf::milliseconds(200), 1, 325, turret}));




}