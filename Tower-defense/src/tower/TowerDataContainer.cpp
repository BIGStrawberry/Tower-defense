#include "TowerDataContainer.h"



std::map<TowerType, TowerData> TowerDataContainer::container = {
		std::pair<TowerType, TowerData>(TowerType::Normal, TowerData{75.0f, sf::milliseconds(500), 1, 75}),  //radius, reload_time, damage, cost
		std::pair<TowerType, TowerData>(TowerType::Slow, TowerData{200.0f, sf::milliseconds(500), 1, 175}),
		std::pair<TowerType, TowerData>(TowerType::Long, TowerData{125.0f, sf::milliseconds(200), 1, 325})
	};

TowerData& TowerDataContainer::get(TowerType type) {
	return container[type];
}