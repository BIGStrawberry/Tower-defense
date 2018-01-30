#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "PlayState.h"
#include "../Player.h"
#include "../helpers/Menu.h"
#include "../helpers/MenuItem.h"

class PauseState: public State {
private:
	sf::Font font;
	sf::Text text;
	Menu menu;
	const Player & player;
public:
	PauseState(sf::RenderWindow& window, Player & player);

	void init() override;
	void update() override;
	void render() const override;
	void cleanUp() override;

	void onKeyPressed(sf::Event& evt) override;
	void onMouseButtonPressed(sf::Event& evt) override;
	void onMouseMoved(sf::Event& evt) override;
};