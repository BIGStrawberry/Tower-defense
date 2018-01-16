#include "PlayState.h"
#include "../helpers/GameStateManager.h"

PlayState::PlayState(sf::RenderWindow& window):
	State(window) {}

void PlayState::init() {
	if (!font.loadFromFile("resources/fonts/consola.ttf")) {
		std::cout << "Could not load consola.ttf" << std::endl;
	}
	text.setFont(font);
	text.setString("Press Esc to go back to menu");
	// TODO: Better center d;)
	text.setPosition({static_cast<float>(window.getSize().x) / 2 - 7 * 24, static_cast<float>(window.getSize().y) / 2 - 24});
}

void PlayState::update() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		GameStateManager::popState();
	}
}

void PlayState::render() const {
	window.draw(text);
}

void PlayState::cleanUp() {}
