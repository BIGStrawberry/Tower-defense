#pragma once
#include <map>
#include "EnemyType.h"
#include "EnemyData.h"
#include <SFML/Graphics.hpp>
#include "../Textures/TextureContainer.h"

#pragma region comment
/**
* @class A container for EnemyData
* @file EnemyDataContainer.cpp
* @details This is a static class, contains the data needed by Enemy.
* Its load() function needs to be called once before the construction
* of the first instance of a class derived from Enemy.
*/
#pragma endregion

class EnemyDataContainer
{
private:
	static std::map<EnemyType, EnemyData> container;
public:
#pragma region comment
	/**
	* @brief loads the data to the container
	* @details This function loads all the data to the container.
	* It also constructs the body sprite for each enemyType's datastruct.
	* Needs to be called before the construction of the first Enemy,
	* otherwise it may causes undefined behavior.
	*/
#pragma endregion
	static void load();
#pragma region comment
	/**
	* @brief returns an EnemyData reference.
	* @param EnemyType	type: The name of the type of unit for which the data is needed.
	* @details This function will return the corresponding EnemyData, according
	* to the given parameter.
	*/
#pragma endregion
	static EnemyData& get(EnemyType type);
};

