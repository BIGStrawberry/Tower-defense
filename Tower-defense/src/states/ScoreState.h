#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "PlayState.h"
#include "MenuState.h"
#include "../helpers/Menu.h"
#include "../helpers/MenuItem.h"

class ScoreState: public State {
private:
	sf::Font font;
	sf::Text text;
	Menu menu;
	uint32_t score;
public:
	ScoreState(sf::RenderWindow& window, uint32_t score);

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