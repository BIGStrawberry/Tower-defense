#include "PlayState.h"
#include "../helpers/GameStateManager.h"

PlayState::PlayState(sf::RenderWindow& window):
	State(window),
	tileSize(31),
	grid(window, tileSize),
	player(window, 15, 75, 0),
	dummyTower(nullptr)
{}

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
		dummyTower = std::make_unique<Tower>(
			window,
			tileSize,
			placePosition,
			static_cast<int>(tileSize) * 2,
			dummyEnemies,
			750
		);
		
	}
};

void PlayState::onMouseButtonPressed(sf::Event& evt) {
	// TODO: The grid should have a position insted of a x/y offset, so that we can substract the position instead of 3
	float fullSize = tileSize + lineSize;
	uint8_t x = static_cast<uint8_t>(ceil(static_cast<float>(placePosition.x) / fullSize)) - 3;
	uint8_t y = static_cast<uint8_t>(ceil(static_cast<float>(placePosition.y) / fullSize)) - 3;

	// sf::RenderWindow & window, float size, sf::Vector2f pos, int radius, std::vector<std::shared_ptr<Enemy>>& enemies, int reload_time
	if (grid.canBePlaced(x,y)) {
		grid.placeTower(x,y,std::make_unique<Tower>(window, tileSize, placePosition, static_cast<int>(tileSize) * 2, dummyEnemies, 750));
		std::cout << "Success!" << std::endl;
		// TODO: Save action in actions list
		if (player.gold >= dummyCost) {
			player.gold -= dummyCost; // TODO: replace this with tower cost
			std::cout << player.gold << std::endl;
		}
	} else {
		std::cout << "Oei" << std::endl;
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
		} else if (player.gold < dummyCost) { // TODO: replace this with tower cost
			dummyTower->setColor(sf::Color::Yellow);
		} else {
			dummyTower->setColor(sf::Color::Green);
		}
	}
};