#pragma once

#include "EnemyAir.h"
#include "EnemyGround.h"
#include <memory>

#pragma region comment
/// \brief
///  makes an Enemy on the heap
/// \param EnemyType - the dataset used by the Enemy.
/// \param sf::RenderWindow& - window to be rerndered on
/// \param Grid& - grid, contains a public vector of sf::Vector2f coordinates, called path.
/// \details
/// This function returns a std::shared_ptr to an Enemy object, created using the given parameters.

#pragma endregion
std::shared_ptr<Enemy> make_enemy(EnemyType type, sf::RenderWindow& window, Grid& grid);