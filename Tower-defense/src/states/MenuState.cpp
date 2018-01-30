#include "MenuState.h"
#include "../helpers/GameStateManager.h"

MenuState::MenuState(sf::RenderWindow& window):
	State(window),
	menu(window, {{
			window,
			std::function<void()>([&window]() { GameStateManager::pushState(std::make_unique<PlayState>(window)); }),
			{250, 75},
			{static_cast<float>(window.getSize().x) / 2 - 250 / 2, 150},
			{"Play game", font, 20}
		}, {
			window,
			std::function<void()>([&window]() { window.close(); }),
			{250, 75},
			{static_cast<float>(window.getSize().x) / 2 - 250 / 2, 350},
			{"Exit game", font, 20}
		}
	})
{}

void MenuState::init() {
	background_music.openFromFile("resources/sounds/background_music.ogg");
	background_music.setLoop(true);
	background_music.play();

	if (!font.loadFromFile("resources/fonts/consola.ttf")) {
		std::cout << "Could not load consola.ttf" << std::endl;
	}
	text.setFont(font);
	text.setString("A Mazing Tower Defence");
	// TODO: Better center d;)
	text.setPosition({static_cast<float>(window.getSize().x) / 2 - 7 * 24, 24.0f});

	for (uint8_t i = 0; i < 4; ++i) {
		if (sf::Joystick::isConnected(i)) {
			easterEgg = std::move(std::make_unique<SpearContainer>(window));
			break;
		}
	}
}

void MenuState::update() {
	if (easterEgg != nullptr) easterEgg->update();
}

void MenuState::render() const {
	window.draw(text);

	if (easterEgg != nullptr) easterEgg->render();
	menu.render();
}

void MenuState::cleanUp() {
}

void MenuState::onKeyPressed(sf::Event& evt) {
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

void MenuState::onMouseButtonPressed(sf::Event& evt) {
	menu.onPress();
}

void MenuState::onMouseMoved(sf::Event& evt) {
	menu.onMouseMoved(evt);
}

void MenuState::onJoystickMoved(sf::Event& evt) {
	if (easterEgg != nullptr) easterEgg->onJoystickMoved(evt);
}

void MenuState::onJoystickConnected(sf::Event& evt) {
	if (easterEgg != nullptr) easterEgg->connectController(evt.joystickConnect.joystickId);
	else easterEgg = std::move(std::make_unique<SpearContainer>(window));
}

void MenuState::onJoystickDisconnected(sf::Event& evt) {
	if (easterEgg != nullptr) easterEgg->disconnectController(evt.joystickConnect.joystickId);
}