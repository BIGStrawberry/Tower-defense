#include "PlayState.h"
#include "../helpers/GameStateManager.h"

PlayState::PlayState(sf::RenderWindow& window):
	State(window),
	grid(window, 31)
{}

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
	grid.update();
}

void PlayState::render() const {
	grid.render();
	window.draw(text);
}

void PlayState::cleanUp() {}

void PlayState::onKeyPressed(sf::Event& evt) {
	if (evt.key.code ==  sf::Keyboard::Escape) {
		// TODO: Pass player score not 1337
		GameStateManager::pushState(std::make_unique<ScoreState>(window, 1337));
	}
};