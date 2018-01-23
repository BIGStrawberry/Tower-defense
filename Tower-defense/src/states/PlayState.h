#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "ScoreState.h"
#include "../Grid.h"
#include "../Player.h"

class PlayState: public State {
private: 
	sf::Font font;
	sf::Text text;
	Player player;
	Grid grid;
public:
	PlayState(sf::RenderWindow& window);

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