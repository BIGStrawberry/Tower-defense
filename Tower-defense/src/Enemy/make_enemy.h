#pragma once

#include "EnemyAir.h"
#include "EnemyGround.h"
#include <memory>

std::shared_ptr<Enemy> make_enemy(EnemyType type, sf::RenderWindow& window, Grid& grid);