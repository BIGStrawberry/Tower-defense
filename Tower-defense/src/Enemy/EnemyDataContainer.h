#pragma once
#include <map>
#include "EnemyType.h"
#include "EnemyData.h"

#pragma region comment
/// \brief
/// class EnemyDataContainer
/// \details
/// Static class, contains a UnitData object for every unit type.
#pragma endregion

class EnemyDataContainer
{
private:
	static std::map<EnemyType, EnemyData> container;
public:
#pragma region comment
	/// \brief
	/// loads the data.
	/// \details
	/// This function loads the data to the container. This function
	/// needs to be called once, before the first Enemy object is constructed.
#pragma endregion
	static void load();
#pragma region comment
	/// \brief
	/// getter for EnemyData
	/// \param EnemyType - returns the data of the given type.
	/// 
#pragma endregion
	static EnemyData& get(EnemyType type);
};

