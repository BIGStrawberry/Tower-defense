#include "Grid.h"
#include <iostream>

Grid::Grid(sf::RenderWindow & window, float tileSize):
	window(window),
	tileSize(tileSize),
	spawn(sf::Vector2f(tileSize,tileSize)),
	base(sf::Vector2f(tileSize,tileSize))
{


	//TODO: cast round the result of the devided numers off, so the spawn will alway's be allinged with the grid
	spawn.setPosition(xOffset - (tileSize + lineSize), static_cast<int>(ROWS / 2) * (tileSize + lineSize) + yOffset);
	spawn.setOrigin(tileSize / 2, tileSize / 2);
	spawn.setFillColor(sf::Color::Red);
	base.setPosition(xOffset + COLUMNS * (tileSize + lineSize), static_cast<int>(ROWS / 2) * (tileSize + lineSize) + yOffset);
	base.setFillColor(sf::Color::Green);
	base.setOrigin(tileSize / 2, tileSize / 2);

	path = {
		spawn.getPosition(),
		spawn.getPosition() + sf::Vector2f{32, 0},
		spawn.getPosition() + sf::Vector2f{32, 32},
		base.getPosition()
	};

	float enemySize = (tileSize + lineSize) / 4;
	for (uint8_t i = 0; i < 5; ++i) {
		std::shared_ptr<Enemy> enemy;
		if (i == 0) {
			enemy = std::make_shared<EnemyGround>(
				window,
				path,
				EnemyType::Normal
			);
		} else {
			enemy = std::make_shared<EnemyAir>(
				window,
				path,
				EnemyType::Flying
			);
		}
		enemies.push_back(enemy);
		// enemy.setPosition((tileSize + lineSize) * i + xOffset + (tileSize+lineSize)/4, yOffset + (tileSize + lineSize) / 4);
		// enemies.emplace_back(enemy);
	}


	for (uint8_t i = 0; i < ROWS; ++i) {
		for (uint8_t j = 0; j < COLUMNS; ++j) {
			if (i % 7 == 0 && j % 5 == 0) {
				sf::Vector2f pos{static_cast<float>(j) * (tileSize + lineSize) + xOffset , static_cast<float>(i) * (tileSize + lineSize) + yOffset};
				placeTower(j, i, std::make_unique<Tower>(window, tileSize, pos, enemies, TowerType::Long));
			}
		}
	}
};

void Grid::update() {
	for (auto& tower : grid) {
		if (tower != nullptr) {
			tower->update();
		}
	}

	for (auto& enemy : enemies) {
		// Somting does not work here
		enemy->update();
	}
}

void Grid::render() const {
	window.draw(spawn);
	window.draw(base);
	for (const auto& tower:grid) {
		if (tower != nullptr) {
			tower->render();
		}
	}
	
	for (const auto & enemy : enemies) {
		enemy->render();
	}
	
}

bool Grid::placeTower(uint8_t x, uint8_t y, std::shared_ptr<Tower> newTower) {
	//checks invalid position and there is already a tower placed on target location
	if (x <= 0 && x >= COLUMNS && 
		y <= 0 && y >= ROWS &&
		grid[x + y * COLUMNS] != nullptr
		) {
		return false;
	}
	grid[x + y * COLUMNS] = newTower;
	//TODO: pathfinding check
	return true;
}
