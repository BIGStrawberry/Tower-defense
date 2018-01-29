#include "EnemyDataContainer.h"

std::map<EnemyType, EnemyData> EnemyDataContainer::container;

void EnemyDataContainer::load()
{
	container = {
		// Hp, speed, damage, gold
		std::pair<EnemyType, EnemyData>(EnemyType::Fast, EnemyData   {6, 6, 1, 25}), 
		std::pair<EnemyType, EnemyData>(EnemyType::Normal, EnemyData {6, 3, 1, 15}),
		std::pair<EnemyType, EnemyData>(EnemyType::Tank, EnemyData   {10, 2, 1, 25}),
		std::pair<EnemyType, EnemyData>(EnemyType::Flying, EnemyData {6, 3, 1, 20})
	};
}

EnemyData& EnemyDataContainer::get(EnemyType type)
{
	return container[type];
}