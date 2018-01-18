#pragma once

#include "EnemyAir.h"
#include "EnemyGround.h"
#include <memory>

#pragma region comment
/**
* @brief creates an Enemy object on th heap.
* @param EnemyTye					type: The type of Enemy that needs to be created.
* @param sf::RenderWindow&			window: The window that the Enemy will be rendered on.
* @param std::vector<sf::Vector2f>&	path: Vector containing the coordinates of the path that
* the unit needs to follow.
* @details This function will create an instance of desired subclass of Enemy on the heap,
* and return a std::shred_ptr<Enemy> to that instance.
*/

#pragma endregion
std::shared_ptr<Enemy> make_enemy(EnemyType type, sf::RenderWindow& window, std::vector<sf::Vector2f>& path);