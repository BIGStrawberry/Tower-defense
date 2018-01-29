#pragma once
#include <SFML/Graphics.hpp>
#pragma region comment
/**
* @struct Encapsulates all the (modifiable) data that is needed by Enemy.
*/
#pragma endregion

struct EnemyData
{
	int hp;
	float speed;
	int damage;
	int gold;
	const sf::Sprite body;
};