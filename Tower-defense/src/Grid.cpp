#include "Grid.h"
#include "helpers\GameStateManager.h"
#include "states\ScoreState.h"


Grid::Grid(sf::RenderWindow & window, float tileSize, Player & player):
	window(window),
	tileSize(tileSize),
	spawn(sf::Vector2f(tileSize, tileSize)),
	base(sf::Vector2f(tileSize, tileSize)),
	player(player),
	pathfinder(grid, COLUMNS, START_INDEX, END_INDEX) {
	//TODO: cast round the result of the devided numers off, so the spawn will alway's be allinged with the grid
	spawn.setPosition(xOffset - (tileSize + lineSize), static_cast<int>(ROWS / 2) * (tileSize + lineSize) + yOffset);
	spawn.setOrigin(tileSize / 2, tileSize / 2);
	spawn.setFillColor(sf::Color::Red);
	base.setPosition(xOffset + COLUMNS * (tileSize + lineSize), static_cast<int>(ROWS / 2) * (tileSize + lineSize) + yOffset);
	base.setFillColor(sf::Color::Green);
	base.setOrigin(tileSize / 2, tileSize / 2);
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
			player.numberOfEnemiesKilled++;
			player.addGold(enemy.getGold());
			enemies.erase(enemies.begin() + i);
			i--;
		} else if (enemy.state == Enemy::States::Reached_Base) {
			player.lives -= enemy.getDmg();
			if (player.lives <= 0) {
				GameStateManager::pushState(std::make_unique<ScoreState>(window, player));
			}
			enemies.erase(enemies.begin() + i);
			i--;
		}
	}

	// Checks if there are enemy's in the waveQueue and places them in the enemies vector (only in wave state)
	if (!preWave && waveQueue.size() > 0 && clock.getElapsedTime() > spawnDelay) {
		clock.restart();
		enemies.push_back(waveQueue.back());
		waveQueue.pop_back();
	} else if (!preWave && waveQueue.size() == 0 && enemies.size() == 0) { // Wave completed
		std::cout << "Wave: " << waveNumber << " completed" << std::endl;
		preWave = true; // Set state to preWave state
		++waveNumber;
		waveClock.restart(); // Start countdown till next wave
	}

	// Starts wave when time is up
	if (preWave && waveClock.getElapsedTime() > waveDelay) {
		startWave();
	}
}


void Grid::calculatePath() {
	path.clear();
	std::vector<int> indexPath = pathfinder.find();
	std::reverse(indexPath.begin(), indexPath.end());

	for (const auto& index : indexPath) {
		// 1d index to 2d index
		uint8_t x = index % COLUMNS;
		uint8_t y = index / COLUMNS;
		sf::Vector2f pos{static_cast<float>(x) * (tileSize + lineSize) + xOffset , static_cast<float>(y) * (tileSize + lineSize) + yOffset};
		path.emplace_back(pos);
	}
}

void Grid::render() const {
	window.draw(spawn);
	window.draw(base);
	for (const auto& tower : grid) {
		if (tower != nullptr) {
			tower->render();
		}
	}

	for (const auto & enemy : enemies) {
		enemy->render();
	}

}

void Grid::startWave() {
	try {
		calculatePath();
	} catch (const UnreachableBase&) {
		// TODO: Place error sound
		return;
	}

	// Wave already started
	if (!preWave) return;

	// Spawn a extra group every 10 waves
	uint16_t numberOfGroups = waveNumber / 10 + 1;
	for (uint16_t i = 0; i < numberOfGroups; ++i) {
		// Tank
		uint32_t randInt = rand() % 100;
		if (waveNumber == TANK_START_WAVE || (waveNumber >= TANK_START_WAVE && randInt <= TANK_SPAWN_RATE)) {
			for (uint8_t i = 0; i < TANK_PER_GROUP; ++i) {
				waveQueue.push_back(make_enemy(EnemyType::Tank, window, path, waveNumber));
			}
		}

		// Normal
		randInt = rand() % 100;
		if (waveNumber == NORMAL_START_WAVE || (waveNumber >= NORMAL_START_WAVE && randInt <= NORMAL_SPAWN_RATE)) {
			for (uint8_t i = 0; i < NORMAL_PER_GROUP; ++i) {
				waveQueue.push_back(make_enemy(EnemyType::Normal, window, path, waveNumber));
			}
		}

		// Speed
		randInt = rand() % 100;
		if (waveNumber == FAST_START_WAVE || (waveNumber >= FAST_START_WAVE && randInt <= FAST_SPAWN_RATE)) {
			for (uint8_t i = 0; i < FAST_PER_GROUP; ++i) {
				waveQueue.push_back(make_enemy(EnemyType::Fast, window, path, waveNumber));
			}
		}

		// Flying
		randInt = rand() % 100;
		if (waveNumber == FLYING_START_WAVE || (waveNumber >= FLYING_START_WAVE && randInt <= FLYING_SPAWN_RATE)) {
			for (uint8_t i = 0; i < FLYING_PER_GROUP; ++i) {
				waveQueue.push_back(make_enemy(EnemyType::Flying, window, path, waveNumber));
			}
		}
	}
	// Reverse the vector so we can use it as a queue
	std::reverse(waveQueue.begin(), waveQueue.end());
	preWave = false;
}

bool Grid::canBePlaced(uint8_t x, uint8_t y) {
	//checks invalid position and there is already a tower placed on target location
	if (!preWave ||
		x < 0 || x >= COLUMNS ||
		y < 0 || y >= ROWS ||
		x + y * COLUMNS == START_INDEX ||
		x + y * COLUMNS == END_INDEX ||
		grid[x + y * COLUMNS] != nullptr
		) {
		return false;
	}

	return true;
}

void Grid::placeTower(uint8_t x, uint8_t y, TowerType towerType, bool saveAction) {
	sf::Vector2f pos{static_cast<float>(x) * (tileSize + lineSize) + xOffset , static_cast<float>(y) * (tileSize + lineSize) + yOffset};
	if (canBePlaced(x, y)) {
		grid[x + y * COLUMNS] = make_tower(window, tileSize, pos, enemies, towerType);
	}

	try {
		calculatePath();

		if (saveAction) {
			player.addAction(x, y, TowerDataContainer::get(towerType).cost, Action::ACTION_TYPE::PLACE_TOWER, towerType);
		}

		// TODO: Maybe its more efficient ask the cost before we put it in the array
		player.removeGold(grid[x + y * COLUMNS]->getCost());
	} catch (const UnreachableBase&) {
		grid[x + y * COLUMNS] = nullptr; // This tower was blocking so we remove it

	}
}

void Grid::upgradeTower(uint8_t x, uint8_t y) {
	grid[x + y * COLUMNS]->upgrade();
	//player. -= grid[x + y * COLUMNS]->getUpgradeCost();
}


void Grid::clearGrid() {
	for (auto & tower : grid) {
		tower = nullptr;
	}
}


std::shared_ptr<Tower> Grid::intersects(sf::Vector2f cursor_pos) {
	for (auto t : grid) {
		if (t) {
			if (t->getBounds().contains(cursor_pos)) {
				return t;
			}
		}
	}
	return nullptr;
}

void Grid::removeTower(std::shared_ptr<Tower> selected) {
	for (auto& p : grid) {
		if (p == selected) {
			p = nullptr;
			player.addAction(static_cast<uint8_t>(selected->getPosition().x), static_cast<uint8_t>(selected->getPosition().y), static_cast<uint32_t>(-0.8 * selected->getCost()), Action::ACTION_TYPE::SELL_TOWER, selected->getType());
			player.addGold(static_cast<uint32_t>(0.8 * selected->getCost()));
			return;
		}
	}
}
