#include "PlayState.h"
#include "../helpers/GameStateManager.h"


PlayState::PlayState(sf::RenderWindow& window):
	State(window),
	player(window, 20, 200, 0),
	grid(window, 31)
{}

void PlayState::rebuildGrid() {
	grid.clearGrid();

	for (auto& action : player.actions) {
		switch (action.type) {
		case Action::ACTION_TYPE::PLACE_TOWER:
			//change 31 to tileSize
			grid.placeTower(
				action.x,
				action.y,
				make_tower(window,
						   static_cast<float>(31),
						   sf::Vector2f{static_cast<float>(action.x) * 31,
						   static_cast<float>(action.y) * 31},
						   dummyEnemies,
						   TowerType::Normal // this should be action.towertype or something
						   )
			);
			break;
		case Action::ACTION_TYPE::SELL_TOWER:
			//TODO: REMOVE TOWER
			//TODO: RETURN GOLD OF TOWER
			//TODO: Call grid.sellTower(), or something like that
			break;
		case Action::ACTION_TYPE::UPGRADE_TOWER:
			//TODO: UPGRADE TOWERS
			//TODO: TAKE GOLD FOR UPGRADING THE TOWER
			//TODO: Call grid.upgradeTower(), or something like that
			break;
		}
	}
}

void PlayState::init() {
	if (!font.loadFromFile("resources/fonts/consola.ttf")) {
		std::cout << "Could not load consola.ttf" << std::endl;
	}
	text.setFont(font);
	text.setString("Press Esc to go back to menu");
	// TODO: Better center d;)
	text.setPosition({static_cast<float>(window.getSize().x) / 2 - 7 * 24, static_cast<float>(window.getSize().y) / 2 - 24});

	player.addAction(20, 10, Action::ACTION_TYPE::PLACE_TOWER, 10);
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
}
