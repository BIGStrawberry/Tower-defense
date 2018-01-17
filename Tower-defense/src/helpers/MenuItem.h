#pragma once

#include <functional>
#include <SFML\Graphics.hpp>

class MenuItem {
private:
	sf::RenderWindow& window;
	std::function<void()> action;
	sf::RectangleShape button;
	sf::Text text;
public:
	MenuItem(sf::RenderWindow& window, std::function<void()> action, sf::Vector2f size, sf::Vector2f position, sf::Text text);

	void onPress();
	void render() const;
	void renderSelected();
};

