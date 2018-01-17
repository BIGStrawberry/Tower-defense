#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "PlayState.h"
#include "../helpers/Menu.h"
#include "../helpers/MenuItem.h"

class MenuState: public State {
private:
	sf::Font font;
	sf::Text text;
	Menu menu;
public:
	MenuState(sf::RenderWindow& window);

	void init() override;
	void update() override;
	void render() const override;
	void cleanUp() override;
};