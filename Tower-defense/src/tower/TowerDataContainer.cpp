#include "TowerDataContainer.h"



std::map<TowerType, TowerData> TowerDataContainer::container = {
		std::pair<TowerType, TowerData>(TowerType::Normal, TowerData{50, 500, 10}),  //radius, reload_time in ms, damage
		std::pair<TowerType, TowerData>(TowerType::Slow, TowerData{25, 500, 10}),
		std::pair<TowerType, TowerData>(TowerType::Long, TowerData{100, 200, 10})
	};

TowerData& TowerDataContainer::get(TowerType type) {
	return container[type];
}