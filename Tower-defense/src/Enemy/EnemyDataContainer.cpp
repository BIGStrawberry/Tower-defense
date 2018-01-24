#include "EnemyDataContainer.h"

std::map<EnemyType, EnemyData> EnemyDataContainer::container;

void EnemyDataContainer::load()
{
	container = {
		std::pair<EnemyType, EnemyData>(EnemyType::Fast, EnemyData{ 5, 8, 1, 50 }), // Hp, speed, damage, gold
		std::pair<EnemyType, EnemyData>(EnemyType::Normal, EnemyData{ 10, 4, 1, 50 }),
		std::pair<EnemyType, EnemyData>(EnemyType::Tank, EnemyData{ 20, 2, 2, 50 }),
		std::pair<EnemyType, EnemyData>(EnemyType::Flying, EnemyData{ 10, 4, 2, 50 })
	};
}

EnemyData& EnemyDataContainer::get(EnemyType type)
{
	return container[type];
}