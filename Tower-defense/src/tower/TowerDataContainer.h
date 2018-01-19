#pragma once
#include <map>
#include "TowerType.h"
#include "TowerData.h"

class TowerDataContainer {
private:
	static std::map<TowerType, TowerData> container;
public:

	static TowerData& get(TowerType type);
};

