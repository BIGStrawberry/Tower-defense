#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "MenuState.h"

class PlayState: public State {
private: 
	sf::Font font;
	sf::Text text;
public:
	PlayState(sf::RenderWindow& window);

	void init() override;
	void update() override;
	void render() const override;
	void cleanUp() override;
};