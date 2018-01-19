#include "EnemyDataContainer.h"

std::map<EnemyType, EnemyData> EnemyDataContainer::container;

void EnemyDataContainer::load()
{
	container = {
		std::pair<EnemyType, EnemyData>(EnemyType::Fast, EnemyData{ 20, 12, 10, 50 }),
		std::pair<EnemyType, EnemyData>(EnemyType::Normal, EnemyData{ 20, 5, 10, 50 }),
		std::pair<EnemyType, EnemyData>(EnemyType::Tank, EnemyData{ 20, 12, 10, 50 }),
		std::pair<EnemyType, EnemyData>(EnemyType::Flying, EnemyData{ 20, 5, 10, 50 })
	};
}

EnemyData& EnemyDataContainer::get(EnemyType type)
{
	return container[type];
}