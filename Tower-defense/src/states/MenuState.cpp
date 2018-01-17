#include "MenuState.h"
#include "../helpers/GameStateManager.h"

MenuState::MenuState(sf::RenderWindow& window):
	State(window),
	menu(window, {
		{window, std::function<void()>([&window]() { GameStateManager::pushState(std::make_unique<PlayState>(window)); }),{150, 50},{50, 150},  {"Play game", font, 20}},
		{window, std::function<void()>([&window]() { window.close(); }),{150, 50},{50, 250}, {"Exit game", font, 20}}
	})
{}

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

	menu.update();
}

void MenuState::render() const {
	window.draw(text);

	menu.render();
}

void MenuState::cleanUp() {
}

void MenuState::onKeyPressed(sf::Event evt) {
	switch (evt.key.code) {
	case sf::Keyboard::Return:
		menu.onPress();
		break;
	case sf::Keyboard::Up:
		menu.selectNext();
		break;
	case sf::Keyboard::Down:
		menu.selectPrevious();
		break;
	}
}
