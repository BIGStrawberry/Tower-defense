#include "PlayState.h"
#include "../helpers/GameStateManager.h"


PlayState::PlayState(sf::RenderWindow& window):
	State(window),
	tileSize(31),
	player(window, 20, 375),
	grid(window, 31, player),
	dummyTower(nullptr)
{}

void PlayState::select(std::shared_ptr<Tower> t)
{
	deselect();
	selected = t;
	selected->setColor(sf::Color::Blue);
	selected->enableRangeRender(true);
}

void PlayState::deselect()
{
	if (selected)
	{
		selected->setColor(sf::Color::White);
		selected->enableRangeRender(false);
		selected = nullptr;
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
			grid.removeTower(action.x, action.y, false);
			break;
		case Action::ACTION_TYPE::UPGRADE_TOWER:
			grid.upgradeTower(action.x, action.y, false);
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
}

void PlayState::update() {
	grid.update();
	if (dummyTower != nullptr) {
		dummyTower->setPosition(placePosition);
	}
}

void PlayState::render() const {
	grid.render();
	window.draw(text);
	if (dummyTower != nullptr) {
		dummyTower->render();
	}
}

void PlayState::cleanUp() {}

void PlayState::onKeyPressed(sf::Event& evt) {
	if (evt.key.code ==  sf::Keyboard::Escape) {
		GameStateManager::pushState(std::make_unique<PauseState>(window, player));
	} else if (evt.key.code == sf::Keyboard::A) {
		deselect();
		float fullSize = tileSize + lineSize;
		auto indexes = sf::Vector2f(
			ceil(static_cast<float>((sf::Mouse::getPosition(window).x) / fullSize)) - 3,
			ceil(static_cast<float>((sf::Mouse::getPosition(window).y) / fullSize)) - 3
		);

		placePosition = sf::Vector2f(indexes.x * fullSize + 80, indexes.y * fullSize + 88);
		dummyTower = make_tower(window,
								static_cast<float>(tileSize),
								placePosition,
								dummyEnemies,
								TowerType::Normal // this should be action.towertype or something
		);
	} else if (evt.key.code == sf::Keyboard::U) {
		// Prevent undo during a wave
		if (grid.isInPreWave()) {
			player.undoAction();
			rebuildGrid();
		}
	} else if (evt.key.code == sf::Keyboard::S) {
		deselect();
		float fullSize = tileSize + lineSize;
		auto indexes = sf::Vector2f(
			ceil(static_cast<float>((sf::Mouse::getPosition(window).x) / fullSize)) - 3,
			ceil(static_cast<float>((sf::Mouse::getPosition(window).y) / fullSize)) - 3
		);
		placePosition = sf::Vector2f(indexes.x * fullSize + 80, indexes.y * fullSize + 88);
		dummyTower = make_tower(window,
								static_cast<float>(tileSize),
								placePosition,
								dummyEnemies,
								TowerType::Long // this should be action.towertype or something
		);
	} else if (evt.key.code == sf::Keyboard::D) {
		dummyTower = make_tower(window,
								static_cast<float>(tileSize),
								sf::Vector2f{
			static_cast<float>(sf::Mouse::getPosition(window).x) * tileSize,
			static_cast<float>(sf::Mouse::getPosition(window).y) * tileSize
		},
								dummyEnemies,
								TowerType::Slow // this should be action.towertype or something
		);
	} else if (evt.key.code == sf::Keyboard::W) {
		grid.startWave();
	}
	else if (evt.key.code == sf::Keyboard::Q)
	{
		if (selected)
		{
			float fullSize = tileSize + lineSize;
			uint8_t x = static_cast<uint8_t>(ceil(static_cast<float>(selected->getPosition().x) / fullSize)) - 3;
			uint8_t y = static_cast<uint8_t>(ceil(static_cast<float>(selected->getPosition().y) / fullSize)) - 3;
			grid.removeTower(x, y);
			deselect();
		}
		
	}
	else if (evt.key.code == sf::Keyboard::Y) {

		if (selected) {
			float fullSize = tileSize + lineSize;
			uint8_t x = static_cast<uint8_t>(ceil(static_cast<float>(selected->getPosition().x) / fullSize)) - 3;
			uint8_t y = static_cast<uint8_t>(ceil(static_cast<float>(selected->getPosition().y) / fullSize)) - 3;

			grid.upgradeTower(x, y);
		}

	}
};

void PlayState::onMouseButtonPressed(sf::Event& evt) {
	if (dummyTower != nullptr) {
		deselect();
		// TODO: The grid should have a position insted of a x/y offset, so that we can substract the position instead of 3
		float fullSize = tileSize + lineSize;
		uint8_t x = static_cast<uint8_t>(ceil(static_cast<float>(placePosition.x) / fullSize)) - 3;
		uint8_t y = static_cast<uint8_t>(ceil(static_cast<float>(placePosition.y) / fullSize)) - 3;

		if (grid.canBePlaced(x, y)) {
			std::cout << "Success!" << std::endl;
			// TODO: Replace dummyCost with actual tower cost, Move tower cost to grid class
			if (player.getGold() >= dummyTower->getCost()) {
				grid.placeTower(x, y, dummyTower->getType(), true);
				dummyTower = nullptr;
			}
			else
			{
				dummyTower = nullptr;
			}
		} else {
			std::cout << "Oei" << std::endl;
		}
	}
	else
	{
		std::shared_ptr<Tower> tmp_tower = grid.intersects(sf::Vector2f(static_cast<float>(evt.mouseButton.x), static_cast<float>(evt.mouseButton.y)));
		if (tmp_tower)
		{
			select(tmp_tower);
		}
		else
		{
			deselect();
		}
	}
}

void PlayState::onMouseMoved(sf::Event& evt) {
	if (dummyTower != nullptr) {
		float fullSize = tileSize + lineSize;
		auto indexes = sf::Vector2f(
			ceil(static_cast<float>(evt.mouseMove.x) / fullSize) - 3,
			ceil(static_cast<float>(evt.mouseMove.y) / fullSize) - 3
		);

		placePosition = sf::Vector2f(indexes.x * fullSize + 80, indexes.y * fullSize + 88);

		if (!grid.canBePlaced(static_cast<uint8_t>(indexes.x), static_cast<uint8_t>(indexes.y))) {
			dummyTower->setColor(sf::Color::Red);
		} else if (player.getGold() < dummyTower->getCost()) { // TODO: replace this with tower cost
			dummyTower->setColor(sf::Color::Yellow);
		} else {
			dummyTower->setColor(sf::Color::Green);
		}
	}
}

