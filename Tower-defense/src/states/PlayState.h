#pragma once

#include <math.h>
#include <memory>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "ScoreState.h"
#include "PauseState.h"
#include "../Grid.h"
#include "../Player.h"
#include "../tower/Tower.h"
#include "../tower/make_tower.h"
#include "../Action/Action.h"
#include "../helpers/Menu.h"
#include "../helpers/MenuItem.h"
#include "../Assets/SoundContainer.h"

class PlayState: public State {
private: 
	sf::Font font;
	float tileSize;
	/**
	* @brief lineSize		The width of the lines between the grid
	*/
	float lineSize = 1;
	float yOffset = 8;
	Player player;
	Grid grid;
	std::shared_ptr<Tower> placementTower;
	std::shared_ptr<Tower> selected;
	std::vector<std::shared_ptr<Enemy>> dummyEnemies;
	sf::Vector2f placePosition, placeIndex;
	sf::Text waveNumberText, livesText, goldText, sellsForText, placementCostText, upgradeCostText, attackDamageText;
	sf::RectangleShape waveTimerRect;
	std::array<std::shared_ptr<Tower>, 3> placeableTowers;
	Menu actionsMenu;

	sf::Sound tower_click_sound;

	/**
	* @brief Sets given tower as selected, changes rendering settings.
	*/
	void select(std::shared_ptr<Tower> t);

	/**
	* @brief Sets rendering settings of selected to default, then sets
	* selected to nullptr.
	*/
	void deselect();
	
	/**
	* @brief function that takes a float number and returns a string with the n decimals
	* @param f			the float that needs to be converted
	* @param n			how many decimals the returned string needs to have
	*/
	std::string floatToDecimalstring(float f, int n);

	/**
	* @brief Sells the selected tower
	*/
	void sell();
	/**
	* @brief Upgrades the selected tower
	*/
	void upgrade();
	/**
	* @brief Undos latest player action
	*/
	void undo();

	/**
	* @brief Switches player to pause state
	*/
	void pause();

public:
	PlayState(sf::RenderWindow& window);

	/**
	* @brief rebuilds the grid based on the actions which the user has performed
	*/
	void rebuildGrid();

	/**
	* @brief sets the tower that will be placed
	*/
	void setPlaceTower(TowerType towerType);

	void init() override;
	void update() override;
	void render() const override;
	void cleanUp() override;

	void onKeyPressed(sf::Event& evt) override;
	void onMouseButtonPressed(sf::Event& evt) override;
	void onMouseMoved(sf::Event& evt) override;
};
