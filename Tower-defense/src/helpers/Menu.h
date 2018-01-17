#pragma once

#include <vector>
#include <SFML\Graphics.hpp>
#include "MenuItem.h"

class Menu {
private:
	sf::RenderWindow& window;
	std::vector<MenuItem> menuItems;
	int8_t selectedIndex = -1;
public:
	Menu(sf::RenderWindow& window, std::vector<MenuItem> menuItems);

	void selectNext();
	void selectPrevious();
	void onPress();
	void update();
	void render() const;
};

