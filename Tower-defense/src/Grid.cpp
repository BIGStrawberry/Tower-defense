#include "Grid.h"
#include "helpers\GameStateManager.h"
#include "states\ScoreState.h"


Grid::Grid(sf::RenderWindow & window, float tileSize, Player & player):
	window(window),
	tileSize(tileSize),
	spawn(sf::Vector2f(tileSize,tileSize)),
	base(sf::Vector2f(tileSize,tileSize)),
	player(player)
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
		waveQueue.push_back(enemy);
	}


	for (uint8_t i = 0; i < ROWS; ++i) {
		for (uint8_t j = 0; j < COLUMNS; ++j) {
			if (i % 7 == 0 && j % 5 == 0) {
				placeTower(j, i, TowerType::Long);
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

	for (size_t i = 0; i < enemies.size(); ++i) {
		Enemy& enemy = *enemies[i];
		if (enemy.state == Enemy::States::Walking) {
			enemy.update();
		} else if (enemy.state == Enemy::States::Dead) {
			player.gold += enemy.getGold();
			enemies.erase(enemies.begin() + i);
			i--;
		} else if (enemy.state == Enemy::States::Reached_Base) {
			player.lives -= enemy.getDmg();
			if (player.lives <= 0) {
				GameStateManager::pushState(std::make_unique<ScoreState>(window, 1337));
			}
			enemies.erase(enemies.begin() + i);
			i--;
		}
	}

	// Checks if there are enemy's in the waveQueue and places them in the enemies vector
	if (waveQueue.size() > 0 &&
		clock.getElapsedTime() > spawnDelay) {
		clock.restart();
		enemies.push_back(waveQueue.back());
		waveQueue.pop_back();
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

bool Grid::canBePlaced(uint8_t x, uint8_t y) {
	//checks invalid position and there is already a tower placed on target location
	if (x < 0 || x >= COLUMNS ||
		y < 0 || y >= ROWS ||
		grid[x + y * COLUMNS] != nullptr
		) {
		return false;
	}

	// TODO: Pathfinding check
	return true;
}

void Grid::placeTower(uint8_t x, uint8_t y, TowerType towerType) {
	if (canBePlaced(x, y)) {
		sf::Vector2f pos{static_cast<float>(x) * (tileSize + lineSize) + xOffset , static_cast<float>(y) * (tileSize + lineSize) + yOffset};
		grid[x + y * COLUMNS] = make_tower(window, tileSize, pos, enemies, towerType);
	}
}

void Grid::clearGrid() {
	for (auto & tower : grid) {
		tower = nullptr;
	}
}
