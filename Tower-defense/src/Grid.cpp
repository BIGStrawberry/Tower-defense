#include "Grid.h"
#include "helpers\GameStateManager.h"
#include "states\ScoreState.h"


Grid::Grid(sf::RenderWindow & window, float tileSize, Player & player):
	window(window),
	tileSize(tileSize),
	spawn(sf::Vector2f(tileSize,tileSize)),
	base(sf::Vector2f(tileSize,tileSize)),
	player(player),
	pathfinder(grid, COLUMNS, START_INDEX, END_INDEX)
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

void Grid::startWave() {
	try {
		calculatePath();
	} catch (const UnreachableBase&) {
		// TODO: Place error sound
		return;
	}

	for (uint8_t i = 0; i < 5; ++i) {
		std::shared_ptr<Enemy> enemy;
		if (i % 4 == 0) {
			enemy = make_enemy(EnemyType::Flying, window, path);
		} else {
			enemy = make_enemy(EnemyType::Normal, window, path);
		}
		waveQueue.push_back(enemy);
	}
}

bool Grid::canBePlaced(uint8_t x, uint8_t y) {
	//checks invalid position and there is already a tower placed on target location
	if (x < 0 || x >= COLUMNS ||
		y < 0 || y >= ROWS ||
		x + y * COLUMNS == START_INDEX ||
		x + y * COLUMNS == END_INDEX ||
		grid[x + y * COLUMNS] != nullptr
		) {
		return false;
	}

	return true;
}

void Grid::placeTower(uint8_t x, uint8_t y, TowerType towerType) {
	sf::Vector2f pos{static_cast<float>(x) * (tileSize + lineSize) + xOffset , static_cast<float>(y) * (tileSize + lineSize) + yOffset};
	if (canBePlaced(x, y)) {
		grid[x + y * COLUMNS] = make_tower(window, tileSize, pos, enemies, towerType);
	}

	try {
		calculatePath();
		player.gold -= grid[x + y * COLUMNS]->getCost(); // TODO: Maybe its more efficient ask the cost before we put it in the array
	} catch (const UnreachableBase&) {
		grid[x + y * COLUMNS] = nullptr; // This tower was blocking so we remove it
	}
}

void Grid::clearGrid() {
	for (auto & tower : grid) {
		tower = nullptr;
	}
}


std::shared_ptr<Tower> Grid::intersects(sf::Vector2f cursor_pos)
{
	for (auto t : grid)
	{
		if (t)
		{
			if (t->getBounds().contains(cursor_pos))
			{
				return t;
			}
		}
	}
	return nullptr;
}

void Grid::removeTower(std::shared_ptr<Tower> selected)
{
	for (auto& p : grid)
	{
		if (p == selected)
		{
			p = nullptr;
			player.addAction(static_cast<uint8_t>(selected->getPosition().x), static_cast<uint8_t>(selected->getPosition().y), static_cast<uint32_t>(-0.8 * selected->getCost()), Action::ACTION_TYPE::SELL_TOWER, selected->getType());
			player.gold += static_cast<uint32_t>(0.8 * selected->getCost());
			return;
		}
	}
}