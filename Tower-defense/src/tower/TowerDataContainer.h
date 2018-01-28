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
* The turret sprite for each tower is constructed here and copied into the data.
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

	/**
	* @brief loads the data to the container
	* @details This function loads all the data to the container.
	* It also constructs the turret sprites for each TowerType and gets the textures from the texturecontainer.
	* Needs to be called before the construction of the first Tower.
	*/
	static void load();
};

