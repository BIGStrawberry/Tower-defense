#include "MenuState.h"
#include "../helpers/GameStateManager.h"

MenuState::MenuState(sf::RenderWindow& window):
	State(window) {}

void MenuState::init() {
	if (!font.loadFromFile("resources/fonts/consola.ttf")) {
		std::cout << "Could not load consola.ttf" << std::endl;
	}
	text.setFont(font);
	text.setString("Press Enter to start");
	// TODO: Better center d;)
	text.setPosition({static_cast<float>(window.getSize().x) / 2 - 7 * 24, static_cast<float>(window.getSize().y) / 2 - 24});
}

void MenuState::update() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		GameStateManager::pushState(std::make_unique<PlayState>(window));
	}
}

void MenuState::render() const {
	window.draw(text);
}

void MenuState::cleanUp() {
}
