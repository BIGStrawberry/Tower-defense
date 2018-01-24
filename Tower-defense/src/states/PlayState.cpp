#include "PlayState.h"
#include "../helpers/GameStateManager.h"


PlayState::PlayState(sf::RenderWindow& window):
	State(window),
	tileSize(31),
	player(window, 20, 375, 0),
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
	player.gold = player.startingGold; // TODO: Replace starting gold with accumulated gold
	grid.clearGrid();

	for (auto& action : player.actions) {
		switch (action.type) {
		case Action::ACTION_TYPE::PLACE_TOWER:
			//change 31 to tileSize
			grid.placeTower(action.x, action.y, action.tower_type);
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
		// TODO: Pass player score not 1337
		GameStateManager::pushState(std::make_unique<ScoreState>(window, 1337));
	} else if (evt.key.code == sf::Keyboard::A) {
		deselect();
		dummyTower = make_tower(window,
								static_cast<float>(tileSize),
								sf::Vector2f{
									static_cast<float>(sf::Mouse::getPosition(window).x) * tileSize,
									static_cast<float>(sf::Mouse::getPosition(window).y) * tileSize
		                        },
								dummyEnemies,
								TowerType::Normal // this should be action.towertype or something
		);
	} else if (evt.key.code == sf::Keyboard::U) {
		player.undoAction();
		rebuildGrid();
	} else if (evt.key.code == sf::Keyboard::S) {
		dummyTower = make_tower(window,
								static_cast<float>(tileSize),
								sf::Vector2f{
			static_cast<float>(sf::Mouse::getPosition(window).x) * tileSize,
			static_cast<float>(sf::Mouse::getPosition(window).y) * tileSize
		},
								dummyEnemies,
								TowerType::Long // this should be action.towertype or something
		);
	} else if (evt.key.code == sf::Keyboard::W) {
		grid.startWave();
	}
	else if (evt.key.code == sf::Keyboard::Q)
	{
		if (selected)
		{
			grid.removeTower(selected);
			deselect();
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
			if (player.gold >= dummyTower->getCost()) {
				player.addAction(x, y, dummyTower->getCost(), Action::ACTION_TYPE::PLACE_TOWER, dummyTower->getType());
				grid.placeTower(x, y, dummyTower->getType());
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
		} else if (player.gold < dummyTower->getCost()) { // TODO: replace this with tower cost
			dummyTower->setColor(sf::Color::Yellow);
		} else {
			dummyTower->setColor(sf::Color::Green);
		}
	}
}

