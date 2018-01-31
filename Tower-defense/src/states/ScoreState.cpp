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
	scoreText("Game over! Your score is: " + std::to_string(calculateScore(player)), font),
	scoreWavesCompleted("Waves completed:   " + std::to_string(player.numberOfWavesCompleted), font),
	scoreTowersPlaced("Towers placed:     " + std::to_string(player.numberOfTowersPlaced), font),
	scoreUpgradesDone("Upgrades done:     " + std::to_string(player.numberOfTowersUpgraded), font),
	scoreEnemiesKilled("Enemies killed:    " + std::to_string(player.numberOfEnemiesKilled), font),
	scoreAccumulatedGold("Total gold earned: " + std::to_string(player.getAccumulatedGold()), font),
	scoreTimePlayed("Time played:       " + formatTime(player.timePlayed), font)
{}


uint32_t ScoreState::calculateScore(const Player & player) {
	return static_cast<int>((player.getAccumulatedGold() * (player.numberOfWavesCompleted * 0.5)));
}

std::string ScoreState::formatTime(sf::Time timePlayed) {
	uint32_t seconds, minutes, hours;

	seconds = static_cast<uint32_t>(timePlayed.asSeconds());
	minutes = seconds / 60;
	hours = minutes / 60;

	std::string formattedTime;
	formattedTime.append(std::to_string(hours));
	formattedTime.append(":");
	formattedTime.append(std::to_string(minutes % 60));
	formattedTime.append(":");
	formattedTime.append(std::to_string(seconds % 60));

	return formattedTime;
}

void ScoreState::init() {
	if (!font.loadFromFile("resources/fonts/consola.ttf")) {
		std::cout << "Could not load consola.ttf" << std::endl;
	}


	// Center text
	sf::FloatRect textRect = scoreText.getGlobalBounds();
	scoreText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	scoreText.setPosition({static_cast<float>(window.getSize().x) / 2, 24.0f});
	scoreText.setFillColor(sf::Color::Black);

	scoreEnemiesKilled.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	scoreEnemiesKilled.setPosition({static_cast<float>(window.getSize().x) / 2, 450.0f});
	scoreEnemiesKilled.setFillColor(sf::Color::Black);

	scoreTowersPlaced.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	scoreTowersPlaced.setPosition({static_cast<float>(window.getSize().x) / 2, 475.0f});
	scoreTowersPlaced.setFillColor(sf::Color::Black);

	scoreUpgradesDone.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	scoreUpgradesDone.setPosition({static_cast<float>(window.getSize().x) / 2, 500.0f});
	scoreUpgradesDone.setFillColor(sf::Color::Black);

	scoreWavesCompleted.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	scoreWavesCompleted.setPosition({static_cast<float>(window.getSize().x) / 2, 525.0f});
	scoreWavesCompleted.setFillColor(sf::Color::Black);

	scoreAccumulatedGold.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	scoreAccumulatedGold.setPosition({static_cast<float>(window.getSize().x) / 2, 550.0f});
	scoreAccumulatedGold.setFillColor(sf::Color::Black);

	scoreTimePlayed.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	scoreTimePlayed.setPosition({static_cast<float>(window.getSize().x) / 2, 575.0f});
	scoreTimePlayed.setFillColor(sf::Color::Black);
}

void ScoreState::update() {
}

void ScoreState::render() const {
	window.draw(scoreText);
	window.draw(scoreEnemiesKilled);
	window.draw(scoreTowersPlaced);
	window.draw(scoreUpgradesDone);
	window.draw(scoreWavesCompleted);
	window.draw(scoreAccumulatedGold);
	window.draw(scoreTimePlayed);
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