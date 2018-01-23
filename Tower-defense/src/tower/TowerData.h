#pragma once
#include "SFML\Graphics.hpp"

#pragma region comment
/**
* @struct Encapsulates all the (modifiable) data that is needed by Tower.
*/
#pragma endregion

struct TowerData {
	float radius;
	sf::Time reload_time;
	int32_t damage;
	int32_t cost;
};