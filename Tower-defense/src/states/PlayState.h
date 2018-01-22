#pragma once

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "ScoreState.h"
#include "../Grid.h"
#include "../Action/Action.h"
#include "../Player.h"
#include "../tower/make_tower.h"

class PlayState: public State {
private: 
	sf::Font font;
	sf::Text text;
	Player player;
	Grid grid;
	std::vector<std::shared_ptr<Enemy>> dummyEnemies;

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
	void onMouseButtonPressed(sf::Event& evt) override {};
	void onMouseButtonReleased(sf::Event& evt) override {};
	void onMouseMoved(sf::Event& evt) override {};
};