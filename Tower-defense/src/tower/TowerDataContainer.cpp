#include "TowerDataContainer.h"



std::map<TowerType, TowerData> TowerDataContainer::container = {
		std::pair<TowerType, TowerData>(TowerType::Normal, TowerData{50.0f, sf::milliseconds(500), 10, 75}),  //radius, reload_time in ms, damage
		std::pair<TowerType, TowerData>(TowerType::Slow, TowerData{25.0f, sf::milliseconds(500), 10, 175}),
		std::pair<TowerType, TowerData>(TowerType::Long, TowerData{100.0f, sf::milliseconds(200), 10, 325})
	};

TowerData& TowerDataContainer::get(TowerType type) {
	return container[type];
}