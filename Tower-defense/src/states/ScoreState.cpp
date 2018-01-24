#include "ScoreState.h"
#include "../helpers/GameStateManager.h"

ScoreState::ScoreState(sf::RenderWindow& window, const Player & player):
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
	player(player),
	scoreText("Game over! Your score is: "  + std::to_string(calculateScore(player)), font),
	scoreWavesCompleted("Waves completed: " + std::to_string(player.numberOfWavesCompleted), font),
	scoreTowersPlaced  ("Towers placed: "   + std::to_string(player.numberOfTowersPlaced), font),
	scoreTowersUpgraded("Towers upgraded: " + std::to_string(player.numberOfTowersUpgraded), font),
	scoreEnemiesKilled ("Enemies killed: "  + std::to_string(player.numberOfEnemiesKilled), font)
{}

uint32_t ScoreState::calculateScore(const Player & player) {
	return  (player.numberOfEnemiesKilled * 10) + 
		(player.numberOfTowersPlaced * 25) +
		(player.numberOfTowersUpgraded * 25) +
	    (player.numberOfWavesCompleted * (player.numberOfWavesCompleted * 10));
}

void ScoreState::init() {
	if (!font.loadFromFile("resources/fonts/consola.ttf")) {
		std::cout << "Could not load consola.ttf" << std::endl;
	}

	//TODO: Better alignment d;)
	scoreText.setPosition({static_cast<float>(window.getSize().x) / 2 - 7 * 24, 24.0f});
	scoreEnemiesKilled.setPosition({static_cast<float>(window.getSize().x) / 2 - 7 * 24, 450.0f});
	scoreTowersPlaced.setPosition({static_cast<float>(window.getSize().x) / 2 - 7 * 24, 475.0f});
	scoreTowersUpgraded.setPosition({static_cast<float>(window.getSize().x) / 2 - 7 * 24, 500.0f});
	scoreWavesCompleted.setPosition({static_cast<float>(window.getSize().x) / 2 - 7 * 24, 525.0f});
}

void ScoreState::update() {
}

void ScoreState::render() const {
	window.draw(scoreText);
	window.draw(scoreEnemiesKilled);
	window.draw(scoreTowersPlaced);
	window.draw(scoreTowersUpgraded);
	window.draw(scoreWavesCompleted);
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