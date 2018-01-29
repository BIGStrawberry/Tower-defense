#include "MenuState.h"
#include "../helpers/GameStateManager.h"

PauseState::PauseState(sf::RenderWindow& window, Player & player):
	State(window),
	menu(window, {{
			window,
			std::function<void()>([&window, &player]() {
				GameStateManager::popState(); //Pops the pause state to return to playstate
				player.gameClock.restart(); // Restart the game clock to not count time in pause state
			}),
			{250, 75},
			{static_cast<float>(window.getSize().x) / 2 - 250 / 2, 150},
			{"Resume Game", font, 20}
		}, {
			window,
			std::function<void()>([&window, &player]() {
				GameStateManager::popState(); //Pops the pause state to return to playstate
				GameStateManager::pushState(std::make_unique<ScoreState>(window, player));
			}),
			{250, 75},
			{static_cast<float>(window.getSize().x) / 2 - 250 / 2, 350},
			{"Forfeit Game", font, 20}
		}
	}),
	player(player),
	text("Game Paused..", font)
{}

void PauseState::init() {
	if (!font.loadFromFile("resources/fonts/consola.ttf")) {
		std::cout << "Could not load consola.ttf" << std::endl;
	}

	// Center text
	sf::FloatRect textRect = text.getGlobalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition({static_cast<float>(window.getSize().x) / 2, 24.0f});
}

void PauseState::update() {}

void PauseState::render() const {
	window.draw(text);
	menu.render();
}

void PauseState::cleanUp() {}

void PauseState::onKeyPressed(sf::Event& evt) {
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

void PauseState::onMouseButtonPressed(sf::Event& evt) {
	menu.onPress();
}

void PauseState::onMouseMoved(sf::Event& evt) {
	menu.onMouseMoved(evt);
}