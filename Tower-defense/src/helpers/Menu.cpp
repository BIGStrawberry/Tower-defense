#include "Menu.h"

Menu::Menu(sf::RenderWindow& window, std::vector<MenuItem> menuItems):
	window(window),
	menuItems(menuItems)
{}

void Menu::update() {
	// TODO: Hover and keyboard effects
	for (const auto& menuItem : menuItems) {
		// Check collision with mouse;
	}
}

void Menu::render() const {
	for (const auto& menuItem : menuItems) {
		menuItem.render();
	}
}

void Menu::selectNext() {
	selectedIndex = (selectedIndex < static_cast<uint8_t>(menuItems.size()) - 1) ? selectedIndex + 1 : 0;
}

void Menu::selectPrevious() {
	selectedIndex = (selectedIndex > 1) ? selectedIndex - 1 : static_cast<uint8_t>(menuItems.size()) - 1;
}