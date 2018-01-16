#pragma once

#include <vector>
#include <SFML\Graphics.hpp>
#include "MenuItem.h"

class Menu {
private:
	sf::RenderWindow& window;
	std::vector<MenuItem> menuItems;
	uint8_t selectedIndex;
public:
	Menu(sf::RenderWindow& window, std::vector<MenuItem> menuItems);

	void selectNext();
	void selectPrevious();
	void update();
	void render() const;
};

