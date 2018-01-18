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
	spawn.setFillColor(sf::Color::Red);
	base.setPosition(xOffset + COLUMNS * (tileSize + lineSize), static_cast<int>(ROWS / 2) * (tileSize + lineSize) + yOffset);
	base.setFillColor(sf::Color::Green);
	for (uint8_t i = 0; i < ROWS; ++i) {
		for(uint8_t j = 0; j < COLUMNS; ++j) {
			std::shared_ptr<sf::RectangleShape> newTower = std::make_shared<sf::RectangleShape>(sf::Vector2f(this->tileSize, this->tileSize));
			newTower->setPosition(static_cast<float>(j) * (tileSize + lineSize) + xOffset , static_cast<float>(i) * (tileSize + lineSize) + yOffset);
			placeTower(j, i, newTower);
		}
	}

	float enemySize = (tileSize + lineSize) / 4;
	for (uint8_t i = 0; i < 5; ++i) {
		sf::CircleShape enemy = sf::CircleShape(enemySize);
		enemy.setFillColor(sf::Color::Blue);
		enemy.setPosition((tileSize + lineSize) * i + xOffset + (tileSize+lineSize)/4, yOffset + (tileSize + lineSize) / 4);
		enemies.emplace_back(enemy);
	}
};

void Grid::render() const {
	window.draw(spawn);
	window.draw(base);
	for (const auto& tower:grid) {
		if (tower != nullptr) {
			window.draw(*tower);
		}
	}
	
	for (const auto & enemy : enemies) {
		window.draw(enemy);
	}
	
}

bool Grid::placeTower(uint8_t x, uint8_t y, std::shared_ptr<sf::RectangleShape> newTower) {
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
