#pragma once

#include <SFML/Graphics.hpp>

class State {
protected:
	sf::RenderWindow& window;
public:
	State(sf::RenderWindow& _window): window(_window) {}

	virtual void init() = 0;
	virtual void update() = 0;
	virtual void render() const = 0;
	virtual void cleanUp() = 0;
};