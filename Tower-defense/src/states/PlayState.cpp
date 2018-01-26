#include "PlayState.h"
#include "../helpers/GameStateManager.h"


PlayState::PlayState(sf::RenderWindow& window):
	State(window),
	tileSize(31),
	player(window, 20, 375),
	grid(window, 31, player),
	placementTower(nullptr),
	waveNumberText("Wave: 999", font, 30),
	livesText("Lives: 999", font, 30),
	goldText("Gold: 999", font, 30),
	waveTimerRect(sf::Vector2f(static_cast<float>(window.getSize().x), 10)),
	actionsMenu(window, {{
			window,
			std::bind(&PlayState::sell, this),
			{85, 30},
			{static_cast<float>(window.getSize().x) / 4, static_cast<float>(window.getSize().y) - 50},
			{"Sell", font, 20}
		},{
			window,
			std::bind(&PlayState::upgrade, this),
			{85, 30},
			{static_cast<float>(window.getSize().x) / 4 + 90, static_cast<float>(window.getSize().y) - 50},
			{"Upgrade", font, 20}
		},{
			window,
			std::bind(&PlayState::undo, this),
			{85, 30},
			{static_cast<float>(window.getSize().x) / 4 + 180, static_cast<float>(window.getSize().y) - 50},
			{"Undo", font, 20}
		}
	})
{}

void PlayState::select(std::shared_ptr<Tower> t) {
	deselect();
	selected = t;
	selected->setColor(sf::Color::Blue);
	selected->enableRangeRender(true);
}

void PlayState::deselect() {
	if (selected) {
		selected->setColor(sf::Color::White);
		selected->enableRangeRender(false);
		selected = nullptr;
	}
}

void PlayState::sell() {

}

void PlayState::upgrade() {

}

void PlayState::undo() {
	// Prevent undo during a wave
	if (grid.isInPreWave()) {
		player.undoAction();
		rebuildGrid();
	}
}

void PlayState::rebuildGrid() {
	grid.clearGrid();
	player.resetGold(); //Sets gold to the accumulatedGold

	for (auto& action : player.actions) {
		switch (action.type) {
		case Action::ACTION_TYPE::PLACE_TOWER:
			//change 31 to tileSize
			grid.placeTower(action.x, action.y, action.tower_type, false);
			break;
		case Action::ACTION_TYPE::SELL_TOWER:
			//TODO: REMOVE
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
void PlayState::setPlaceTower(TowerType towerType) {
	placementTower = make_tower(window,
							static_cast<float>(tileSize),
							sf::Vector2f{
								static_cast<float>(sf::Mouse::getPosition(window).x),
								static_cast<float>(sf::Mouse::getPosition(window).y)
							},
							dummyEnemies,
							towerType
	);
}

void PlayState::init() {
	if (!font.loadFromFile("resources/fonts/consola.ttf")) {
		std::cout << "Could not load consola.ttf" << std::endl;
	}
	
	// In game stats
	sf::FloatRect waveTextRect = waveNumberText.getGlobalBounds();
	waveNumberText.setOrigin({waveTextRect.left + waveTextRect.width / 2, 0});
	waveNumberText.setPosition({static_cast<float>(window.getSize().x) * 0.25f, (tileSize + lineSize)});

	sf::FloatRect livesTextRect = livesText.getGlobalBounds();
	livesText.setOrigin({livesTextRect.left + livesTextRect.width / 2, 0});
	livesText.setPosition({static_cast<float>(window.getSize().x) * 0.5f, (tileSize + lineSize)});

	sf::FloatRect goldTextRect = goldText.getGlobalBounds();
	goldText.setOrigin({goldTextRect.left + goldTextRect.width / 2, 0});
	goldText.setPosition({static_cast<float>(window.getSize().x) * 0.75f, (tileSize + lineSize)});
	
	// Wave timer
	waveTimerRect.setPosition(0, 0);
	waveTimerRect.setFillColor(sf::Color::Red);

	// Placeable towers
	const float xOffset = (tileSize + lineSize) + 10;
	const float xPos = static_cast<float>(window.getSize().x) / 10;
	const float yOffset = 35;
	const float yPos = static_cast<float>(window.getSize().y);
	placeableTowers[0] = make_tower(window, tileSize, {xPos, yPos - yOffset}, dummyEnemies, TowerType::Normal);
	placeableTowers[1] = make_tower(window, tileSize, {xPos + xOffset, yPos - yOffset}, dummyEnemies, TowerType::Long);
	placeableTowers[2] = make_tower(window, tileSize, {xPos + xOffset * 2, yPos - yOffset}, dummyEnemies, TowerType::Slow);
}

void PlayState::update() {
	grid.update();
	if (placementTower != nullptr) {
		placementTower->setPosition(placePosition);
	}
	waveNumberText.setString("Wave: " + std::to_string(grid.getWaveNumber()));
	livesText.setString("Lives: " + std::to_string(player.lives));
	goldText.setString("Gold: " + std::to_string(player.getGold()));
	waveTimerRect.setSize({static_cast<float>(window.getSize().x) - static_cast<float>(window.getSize().x) / grid.getWaveDelay().asSeconds() * grid.getWaveClock().asSeconds(), 15});
}

void PlayState::render() const {
	grid.render();
	window.draw(waveNumberText);
	window.draw(livesText);
	window.draw(goldText);
	window.draw(waveTimerRect);
	actionsMenu.render();
	for (const auto& tower : placeableTowers) {
		tower->render();
	}
	if (placementTower != nullptr) {
		placementTower->render();
	}
}

void PlayState::cleanUp() {}

void PlayState::onKeyPressed(sf::Event& evt) {
	if (evt.key.code ==  sf::Keyboard::Escape) {
		GameStateManager::pushState(std::make_unique<PauseState>(window, player));
	} else if (evt.key.code == sf::Keyboard::A) {
		deselect();
		setPlaceTower(TowerType::Normal);
	} else if (evt.key.code == sf::Keyboard::U) {
		undo();
	} else if (evt.key.code == sf::Keyboard::S) {
		setPlaceTower(TowerType::Long);
	} else if (evt.key.code == sf::Keyboard::W) {
		grid.startWave();
	} else if (evt.key.code == sf::Keyboard::Q) {
		if (selected) {
			grid.removeTower(selected);
			deselect();
		}
	}
};

void PlayState::onMouseButtonPressed(sf::Event& evt) {
	actionsMenu.onPress();

	if (placementTower != nullptr) {
		deselect();
		// TODO: The grid should have a position insted of a x/y offset, so that we can substract the position instead of 3
		float fullSize = tileSize + lineSize;
		uint8_t x = static_cast<uint8_t>(ceil(static_cast<float>(placePosition.x) / fullSize)) - 3;
		uint8_t y = static_cast<uint8_t>(ceil(static_cast<float>(placePosition.y) / fullSize)) - 3;

		if (grid.canBePlaced(x, y)) {
			std::cout << "Success!" << std::endl;
			// TODO: Replace dummyCost with actual tower cost, Move tower cost to grid class
			if (player.getGold() >= placementTower->getCost()) {
				grid.placeTower(x, y, placementTower->getType(), true);
				placementTower = nullptr;
			} else {
				placementTower = nullptr;
			}
		} else {
			std::cout << "Oei" << std::endl;
		}
	} else if (waveTimerRect.getGlobalBounds().contains(static_cast<float>(evt.mouseButton.x), static_cast<float>(evt.mouseButton.y))) {
		grid.startWave();
	} else {
		std::shared_ptr<Tower> tmp_tower = grid.intersects(sf::Vector2f(static_cast<float>(evt.mouseButton.x), static_cast<float>(evt.mouseButton.y)));
		if (tmp_tower) {
			select(tmp_tower);
		} else {
			deselect();
		}
	}

	for (const auto& UITower : placeableTowers) {
		if (UITower->getBounds().contains(sf::Vector2f(static_cast<float>(evt.mouseButton.x), static_cast<float>(evt.mouseButton.y)))) {
			setPlaceTower(UITower->getType());
		}
	}
}

void PlayState::onMouseMoved(sf::Event& evt) {
	actionsMenu.onMouseMoved(evt);

	if (placementTower != nullptr) {
		float fullSize = tileSize + lineSize;
		auto indexes = sf::Vector2f(
			ceil(static_cast<float>(evt.mouseMove.x) / fullSize) - 3,
			ceil(static_cast<float>(evt.mouseMove.y) / fullSize) - 3
		);

		placePosition = sf::Vector2f(indexes.x * fullSize + 80, indexes.y * fullSize + 88);

		if (!grid.canBePlaced(static_cast<uint8_t>(indexes.x), static_cast<uint8_t>(indexes.y))) {
			placementTower->setColor(sf::Color::Red);
		} else if (player.getGold() < placementTower->getCost()) { // TODO: replace this with tower cost
			placementTower->setColor(sf::Color::Yellow);
		} else {
			placementTower->setColor(sf::Color::Green);
		}
	}
}

