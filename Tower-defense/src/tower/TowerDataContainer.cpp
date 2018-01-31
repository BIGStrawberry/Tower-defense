#include "TowerDataContainer.h"
#include <iostream>


std::map<TowerType, TowerData> TowerDataContainer::container; 

TowerData& TowerDataContainer::get(TowerType type) {
	return container[type];
}



void TowerDataContainer::load() {

	std::array<sf::Sprite, 3> turret_sprites;
	turret_sprites[0].setOrigin(22.5f, 13.f);
	turret_sprites[0].setTexture(TextureContainer::get("normal_level1.png"));

	turret_sprites[1].setOrigin(22.5f, 13.f);
	turret_sprites[1].setTexture(TextureContainer::get("normal_level2.png"));


	turret_sprites[2].setOrigin(22.5f, 13.f);
	turret_sprites[2].setTexture(TextureContainer::get("normal_level3.png"));

	
	container.insert(std::pair<TowerType, TowerData>(TowerType::Normal, TowerData{75.0f, sf::milliseconds(500), 2, 75, turret_sprites}));

	turret_sprites[0].setOrigin(22.5f, 13.f);
	turret_sprites[0].setTexture(TextureContainer::get("slow_level1.png"));

	turret_sprites[1].setOrigin(22.5f, 13.f);
	turret_sprites[1].setTexture(TextureContainer::get("slow_level2.png"));

	turret_sprites[2].setOrigin(22.5f, 13.f);
	turret_sprites[2].setTexture(TextureContainer::get("slow_level3.png"));



	container.insert(std::pair<TowerType, TowerData>(TowerType::Slow, TowerData{50.0f, sf::milliseconds(500), 1, 175, turret_sprites}));

	turret_sprites[0].setOrigin(22.5f, 13.f);
	turret_sprites[0].setTexture(TextureContainer::get("long_level1.png"));


	turret_sprites[1].setOrigin(22.5f, 13.f);
	turret_sprites[1].setTexture(TextureContainer::get("long_level2.png"));


	turret_sprites[2].setOrigin(22.5f, 13.f);
	turret_sprites[2].setTexture(TextureContainer::get("long_level3.png"));


	container.insert(std::pair<TowerType, TowerData>(TowerType::Long, TowerData{125.0f, sf::milliseconds(1000), 8, 325, turret_sprites}));




}