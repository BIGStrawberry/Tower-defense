#pragma once
#include <SFML/Graphics.hpp>
#pragma region comment
/**
* @struct Encapsulates all the (modifiable) data that is needed by Enemy.
*/
#pragma endregion

struct EnemyData
{
	float hp;
	float speed;
	int32_t damage;
	int32_t gold;
	sf::Sprite body;
};