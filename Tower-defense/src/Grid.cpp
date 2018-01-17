#include "Grid.h"
#include <iostream>

Grid::Grid(sf::RenderWindow & window, float tileSize):
	window(window),
	tileSize(tileSize),
	spawn(sf::Vector2f(tileSize,tileSize)),
	base(sf::Vector2f(tileSize,tileSize))
{
	//TODO: cast round the result of the devided numers off, so the spawn will alway's be allinged with the grid
	//TODO: remove grid lines (tileSize + 1 ) => tileSize
	spawn.setPosition(xOffset - (tileSize + 1), static_cast<int>(ROWS / 2) * (tileSize + 1) + yOffset);
	spawn.setFillColor(sf::Color::Green);
	base.setPosition(xOffset + COLUMNS * (tileSize + 1), static_cast<int>(ROWS / 2) * (tileSize + 1) + yOffset);
	base.setFillColor(sf::Color::Green);
	for (uint8_t i = 0; i < ROWS; ++i) {
		for(uint8_t j = 0; j < COLUMNS; ++j) {
			std::shared_ptr<sf::RectangleShape> newTower = std::make_shared<sf::RectangleShape>(sf::Vector2f(this->tileSize, this->tileSize));
			//TODO remove grid lines (tileSize + 1 ) => tileSize
			newTower->setPosition((static_cast<float>(j) + 2) * (tileSize + 1) , (static_cast<float>(i) + 2) * (tileSize + 1) + 8);
			placeTower(j, i, newTower);
		}
	}
	for (uint8_t i = 0; i < 5; ++i) {
		sf::CircleShape enemy = sf::CircleShape(10);
		enemy.setFillColor(sf::Color::Red);
		enemy.setPosition(static_cast<float>(20) * i, 10);
		enemies.emplace_back(enemy);
	}
};

void Grid::render() const {
	window.draw(spawn);
	window.draw(base);
	for (const auto& tower:towers) {
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
		towers[x + y * COLUMNS] != nullptr
		) {
		return false;
	}
	towers[x + y * COLUMNS] = newTower;
	//TODO: pathfinding check
	return true;
}
