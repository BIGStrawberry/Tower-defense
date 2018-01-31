#include "PlayState.h"
#include "../helpers/GameStateManager.h"
#include <iomanip>
#include <sstream>


PlayState::PlayState(sf::RenderWindow& window):
	State(window),
	tileSize(31),
	player(window, 20, 375000),
	grid(window, 31, player),
	placementTower(nullptr),
	waveNumberText("Wave: 999", font, 30),
	livesText("Lives: 999", font, 30),
	goldText("Gold: 999", font, 30),
	placementCostText("Cost: 999", font, 20),
	sellsForText("Sells for: 999", font, 20),
	upgradeCostText("Upgrade cost: 999", font, 20),
	attackDamageText("Ad: 999", font, 20),
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
		},{
			window,
			std::bind(&PlayState::pause, this),
			{85, 30},
			{static_cast<float>(window.getSize().x) / 4 + 270, static_cast<float>(window.getSize().y) - 50},
			{"Pause", font, 20}
		}
	}),
	tower_click_sound(SoundContainer::get("menu_click.ogg"))
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
	if (selected) {
		float fullSize = tileSize + lineSize;
		uint8_t x = static_cast<uint8_t>(ceil(static_cast<float>(selected->getPosition().x) / fullSize)) - 3;
		uint8_t y = static_cast<uint8_t>(ceil(static_cast<float>(selected->getPosition().y) / fullSize)) - 3;
		grid.removeTower(x, y);
		deselect();
	}
}

void PlayState::upgrade() {
	if (selected) {
		if (player.getGold() >= selected->getUpgradeCost()) {

			float fullSize = tileSize + lineSize;
			uint8_t x = static_cast<uint8_t>(ceil(static_cast<float>(selected->getPosition().x) / fullSize)) - 3;
			uint8_t y = static_cast<uint8_t>(ceil(static_cast<float>(selected->getPosition().y) / fullSize)) - 3;

			grid.upgradeTower(x, y);
		}
	}
}

void PlayState::undo() {
	// Prevent undo during a wave
	if (grid.isInPreWave()) {
		deselect();
		player.undoAction();
		rebuildGrid();
	}
}

void PlayState::pause() {
	GameStateManager::pushState(std::make_unique<PauseState>(window, player));
	player.timePlayed += player.gameClock.getElapsedTime();
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
			grid.removeTower(action.x, action.y, false);
			break;
		case Action::ACTION_TYPE::UPGRADE_TOWER:
			grid.upgradeTower(action.x, action.y, false);
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

std::string PlayState::floatToDecimalstring(float f, int n) {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(n) << f;
	return stream.str();
}

void PlayState::init() {
	if (!font.loadFromFile("resources/fonts/consola.ttf")) {
		std::cout << "Could not load consola.ttf" << std::endl;
	}

	// In game stats
	sf::FloatRect waveTextRect = waveNumberText.getGlobalBounds();
	waveNumberText.setOrigin({waveTextRect.left + waveTextRect.width / 2, 0});
	waveNumberText.setPosition({static_cast<float>(window.getSize().x) * 0.25f, (tileSize + lineSize)});
	waveNumberText.setFillColor(sf::Color::Black);

	sf::FloatRect livesTextRect = livesText.getGlobalBounds();
	livesText.setOrigin({livesTextRect.left + livesTextRect.width / 2, 0});
	livesText.setPosition({static_cast<float>(window.getSize().x) * 0.5f, (tileSize + lineSize)});
	livesText.setFillColor(sf::Color::Black);

	sf::FloatRect goldTextRect = goldText.getGlobalBounds();
	goldText.setOrigin({goldTextRect.left + goldTextRect.width / 2, 0});
	goldText.setPosition({static_cast<float>(window.getSize().x) * 0.75f, (tileSize + lineSize)});
	goldText.setFillColor(sf::Color::Black);

	sf::FloatRect sellsForTextRect = sellsForText.getGlobalBounds();
	sellsForText.setOrigin({sellsForTextRect.left + sellsForTextRect.width / 2, sellsForTextRect.top + sellsForTextRect.height / 2});
	sellsForText.setPosition({static_cast<float>(window.getSize().x) * 0.6f, static_cast<float>(window.getSize().y) - 50});
	sellsForText.setFillColor(sf::Color::Black);

	sf::FloatRect placementCostTextRect = placementCostText.getGlobalBounds();
	placementCostText.setOrigin({placementCostTextRect.left + placementCostTextRect.width / 2, placementCostTextRect.top + placementCostTextRect.height / 2});
	placementCostText.setPosition({static_cast<float>(window.getSize().x) * 0.5775f, static_cast<float>(window.getSize().y) - 20});
	placementCostText.setFillColor(sf::Color::Black);

	sf::FloatRect upgradeCostTextRect = upgradeCostText.getGlobalBounds();
	upgradeCostText.setOrigin({upgradeCostTextRect.left + upgradeCostTextRect.width / 2, upgradeCostTextRect.top + upgradeCostTextRect.height /2});
	upgradeCostText.setPosition({static_cast<float>(window.getSize().x) * 0.6125f, static_cast<float>(window.getSize().y) - 20});
	upgradeCostText.setFillColor(sf::Color::Black);

	sf::FloatRect attackDamageTextRect = attackDamageText.getGlobalBounds();
	attackDamageText.setOrigin({attackDamageTextRect.left + attackDamageTextRect.width / 2, attackDamageTextRect.top + attackDamageTextRect.height / 2 });
	attackDamageText.setPosition({static_cast<float>(window.getSize().x) * 0.725f, static_cast<float>(window.getSize().y) - 50});
	attackDamageText.setFillColor(sf::Color::Black);

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

	//  Reset time played d:)
	player.gameClock.restart();
}

void PlayState::update() {
	grid.update();
	if (placementTower != nullptr) {
		placementTower->setPosition(placePosition);
		sellsForText.setString("Sells for:    " + std::to_string(placementTower->getSellPrice()));
		placementCostText.setString("Cost:         " + std::to_string(placementTower->getUpgradeCost()));
		attackDamageText.setString("Attack damage: " + floatToDecimalstring(placementTower->getDamage(), 2));
	}
	if (selected != nullptr) {
		sellsForText.setString("Sells for:    " + std::to_string(selected->getSellPrice()));
		upgradeCostText.setString("Upgrade cost: " + std::to_string(selected->getUpgradeCost()));
		attackDamageText.setString("Attack damage: " + floatToDecimalstring(selected->getDamage(), 2));
	}
	waveNumberText.setString("Wave: " + std::to_string(grid.getWaveNumber()));
	livesText.setString("Lives: " + std::to_string(player.lives));
	goldText.setString("Gold: " + std::to_string(player.getGold()));
	waveTimerRect.setSize({static_cast<float>(window.getSize().x) - static_cast<float>(window.getSize().x) / grid.getWaveDelay().asSeconds() * grid.getWaveClock().asSeconds(), 15});
}

void PlayState::render() const {
	grid.render();
	if (selected != nullptr) {
		window.draw(sellsForText);
		window.draw(upgradeCostText);
		window.draw(attackDamageText);
	}
	if (placementTower != nullptr) {
		window.draw(sellsForText);
		window.draw(placementCostText);
		window.draw(attackDamageText);
	}
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
		pause();
	} else if (evt.key.code == sf::Keyboard::A) {
		deselect();
		setPlaceTower(TowerType::Normal);
		placementTower->enableRangeRender(true);
	} else if (evt.key.code == sf::Keyboard::U) {
		undo();
	} else if (evt.key.code == sf::Keyboard::S) {
	    deselect();
		setPlaceTower(TowerType::Long);
		placementTower->enableRangeRender(true);
	} else if (evt.key.code == sf::Keyboard::W) {
		grid.startWave();
	} else if (evt.key.code == sf::Keyboard::Q) {
		if (selected) {
			float fullSize = tileSize + lineSize;
			uint8_t x = static_cast<uint8_t>(ceil(static_cast<float>(selected->getPosition().x) / fullSize)) - 3;
			uint8_t y = static_cast<uint8_t>(ceil(static_cast<float>(selected->getPosition().y) / fullSize)) - 3;
			grid.removeTower(x, y);
			deselect();
		}
	} else if (evt.key.code == sf::Keyboard::D) {
		deselect();
		setPlaceTower(TowerType::Slow);
		placementTower->enableRangeRender(true);
	} 
	else if (evt.key.code == sf::Keyboard::Y) {
		if (selected) {
			if (player.getGold() >= selected->getUpgradeCost()) {

				float fullSize = tileSize + lineSize;
				uint8_t x = static_cast<uint8_t>(ceil(static_cast<float>(selected->getPosition().x) / fullSize)) - 3;
				uint8_t y = static_cast<uint8_t>(ceil(static_cast<float>(selected->getPosition().y) / fullSize)) - 3;

				grid.upgradeTower(x, y);
			}
		}
	}
};

void PlayState::onMouseButtonPressed(sf::Event& evt) {
	actionsMenu.onPress();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		placementTower = nullptr;
	}
	else if (placementTower != nullptr) {
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
			tower_click_sound.play();//towerclick sound
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



