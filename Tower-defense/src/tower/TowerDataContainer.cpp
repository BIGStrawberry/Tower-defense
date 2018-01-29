#include "TowerDataContainer.h"



std::map<TowerType, TowerData> TowerDataContainer::container = {
	//radius, reload_time, damage, cost
	std::pair<TowerType, TowerData>(
			TowerType::Normal, TowerData {75.0f,  sf::milliseconds(500),  2, 75}),  
	std::pair<TowerType, TowerData>(
			TowerType::Long, TowerData   {125.0f, sf::milliseconds(1000), 8, 325}),
	std::pair<TowerType, TowerData>(
			TowerType::Slow, TowerData   {50.0f,  sf::milliseconds(500),  1, 175})
};

TowerData& TowerDataContainer::get(TowerType type) {
	return container[type];
}