#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "PlayState.h"

class MenuState: public State {
private:
	sf::Font font;
	sf::Text text;
public:
	MenuState(sf::RenderWindow& window);

	void init() override;
	void update() override;
	void render() const override;
	void cleanUp() override;
};