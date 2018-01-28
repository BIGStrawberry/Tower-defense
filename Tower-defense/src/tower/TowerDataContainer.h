#pragma once
#include <map>
#include "TowerType.h"
#include "TowerData.h"
#include "../Textures/TextureContainer.h"

#pragma region comment
/**
* @class A container for TowerData
* @file TowerDataContainer.cpp
* @details This is a static class, contains the data that differentiates one tower type from another.
* A tower can get the data for it's type here.
*/
#pragma endregion


class TowerDataContainer {
private:
	/*
	@brief a map with keys TowerType and the corresponding values TowerData. 
	
	*/
	static std::map<TowerType, TowerData> container;
public:
	/*
	@brief returns a TowerData reference for the given TowerType.
	*/
	static TowerData& get(TowerType type);


	static void load();
};

