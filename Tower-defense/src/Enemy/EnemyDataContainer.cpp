#include "EnemyDataContainer.h"

std::map<EnemyType, EnemyData> EnemyDataContainer::container;

void EnemyDataContainer::load()
{
	container = {
		std::pair<EnemyType, EnemyData>(EnemyType::Fast, EnemyData{ 10, 8, 0, 15 }), // Hp, speed, damage, gold
		std::pair<EnemyType, EnemyData>(EnemyType::Normal, EnemyData{ 6, 3, 0, 15 }),
		std::pair<EnemyType, EnemyData>(EnemyType::Tank, EnemyData{ 8, 2, 0, 15 }),
		std::pair<EnemyType, EnemyData>(EnemyType::Flying, EnemyData{ 15, 4, 0, 15 })
	};
}

EnemyData& EnemyDataContainer::get(EnemyType type)
{
	return container[type];
}