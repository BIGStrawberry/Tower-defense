#pragma once

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "PlayState.h"
#include "../helpers/Menu.h"
#include "../helpers/MenuItem.h"
#include "../spear/SpearContainer.h"

class MenuState: public State {
private:
	sf::Font font;
	sf::Text text;
	Menu menu;
	std::unique_ptr<SpearContainer> easterEgg;
public:
	MenuState(sf::RenderWindow& window);

	void init() override;
	void update() override;
	void render() const override;
	void cleanUp() override;

	void onKeyPressed(sf::Event& evt) override;
	void onMouseButtonPressed(sf::Event& evt) override;
	void onMouseMoved(sf::Event& evt) override;
	void onJoystickMoved(sf::Event& evt) override;
	void onJoystickConnected(sf::Event& evt) override;
	void onJoystickDisconnected(sf::Event& evt) override;

};