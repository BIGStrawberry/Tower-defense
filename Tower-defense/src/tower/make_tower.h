#pragma once

#include <memory>
#include "Tower.h"
#include "TowerSlow.h"

/**
* @brief returns a shared_ptr to a Tower
* @details This function returns a shared_ptr of Tower or TowerSlow depending on TowerType.
* 
*/

std::shared_ptr<Tower> make_tower(sf::RenderWindow & window, float size, sf::Vector2f pos, std::vector<std::shared_ptr<Enemy>>& enemies, TowerType type);
