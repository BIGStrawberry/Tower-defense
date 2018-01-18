#include "ScoreState.h"
#include "../helpers/GameStateManager.h"

ScoreState::ScoreState(sf::RenderWindow& window, uint32_t score):
	State(window),
	menu(window, {{
			window,
			std::function<void()>([&window]() {
				GameStateManager::popState(); // remove this state
				GameStateManager::popState(); // remove old play state
				GameStateManager::pushState(std::make_unique<PlayState>(window));
            }),
			{250, 75},
			{static_cast<float>(window.getSize().x) / 2 - 255 / 2, 150},
			{"Play again", font, 20}
		}, {
			window,
			std::function<void()>([&window]() {
				GameStateManager::popState(); // remove this state
				GameStateManager::popState(); // remove old play state
				// We are back at the MenuState
		    }),
			{250, 75},
			{static_cast<float>(window.getSize().x) / 2 - 255 / 2, 350},
			{"Back to Menu", font, 20}
		}
	}),
	score(score)
{}

void ScoreState::init() {
	if (!font.loadFromFile("resources/fonts/consola.ttf")) {
		std::cout << "Could not load consola.ttf" << std::endl;
	}
	text.setFont(font);
	std::string str("Game over! Your score: ");
	str += std::to_string(static_cast<int>(score));
	text.setString(str);
	// TODO: Better center d;)
	text.setPosition({static_cast<float>(window.getSize().x) / 2 - 7 * 24, 24.0f});
}

void ScoreState::update() {
}

void ScoreState::render() const {
	window.draw(text);

	menu.render();
}

void ScoreState::cleanUp() {
}

void ScoreState::onKeyPressed(sf::Event& evt) {
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

void ScoreState::onMouseButtonPressed(sf::Event& evt) {
	menu.onPress();
}

void ScoreState::onMouseMoved(sf::Event& evt) {
	menu.onMouseMoved(evt);
}