#include "Menu.h"

Menu::Menu(sf::RenderWindow& window, std::vector<MenuItem> menuItems):
	window(window),
	menuItems(menuItems)
{}

void Menu::selectNext() {
	selectedIndex = (selectedIndex < static_cast<uint8_t>(menuItems.size()) - 1) ? selectedIndex + 1 : 0;
}

void Menu::selectPrevious() {
	selectedIndex = (selectedIndex > 1) ? selectedIndex - 1 : static_cast<uint8_t>(menuItems.size()) - 1;
}

void Menu::onPress() {
	if (selectedIndex != -1) {
		menuItems[selectedIndex].onPress();
	}
}

void Menu::update() {
	// TODO: Hover and keyboard effects
	for (const auto& menuItem : menuItems) {
		// Check collision with mouse;
	}
}

void Menu::render() const {
	for (uint8_t i = 0; i < menuItems.size(); ++i) {
		auto menuItem = menuItems[i];
		if (i == selectedIndex) {
			menuItem.renderSelected();
		} else {
			menuItem.render();
		}
	}
}