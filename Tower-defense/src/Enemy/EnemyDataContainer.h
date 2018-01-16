#pragma once
#include <map>
#include "EnemyType.h"
#include "EnemyData.h"

class EnemyDataContainer
{
private:
	static std::map<EnemyType, EnemyData> container;
public:
	static void load();
	static EnemyData& get(EnemyType type);
};

