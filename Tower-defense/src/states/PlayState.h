#pragma once

#include <math.h>
#include <memory>
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "ScoreState.h"
#include "../Grid.h"
#include "../tower/Tower.h"
#include "../Action/Action.h"
#include "../Player.h"

class PlayState: public State {
private: 
	sf::Font font;
	sf::Text text;
	float tileSize;
	/**
	* @brief lineSize		The width of the lines between the grid
	*/
	float lineSize = 1;
	float yOffset = 8;
	Player player;
	Grid grid;
	std::unique_ptr<Tower> dummyTower;
	uint32_t dummyCost = 10;
	std::vector<std::shared_ptr<Enemy>> dummyEnemies;
	sf::Vector2f placePosition;
public:
	PlayState(sf::RenderWindow& window);

	/**
	* @brief rebuilds the grid based on the actions which the user has performed
	*/
	void rebuildGrid();

	void init() override;
	void update() override;
	void render() const override;
	void cleanUp() override;

	void onKeyPressed(sf::Event& evt) override;
	void onKeyReleased(sf::Event& evt) override {};
	void onMouseButtonPressed(sf::Event& evt) override;
	void onMouseButtonReleased(sf::Event& evt) override {};
	void onMouseMoved(sf::Event& evt) override;
};