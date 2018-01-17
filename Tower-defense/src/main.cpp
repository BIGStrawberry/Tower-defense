#include <SFML/Graphics.hpp>
#include "Enemy\EnemyGround.h"
#include "Enemy\EnemyAir.h"
#include "Enemy\make_enemy.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Project name");
	window.setVerticalSyncEnabled(true);
	sf::Event event;

	EnemyDataContainer::load();

#pragma region Fake_grid
	Grid grid;
	grid.path.push_back(sf::Vector2f(0.0, 0.0));
	grid.path.push_back(sf::Vector2f(100.0, 0.0));
	grid.path.push_back(sf::Vector2f(100.0, 100.0));
	grid.path.push_back(sf::Vector2f(275.0, 300.0));
	grid.path.push_back(sf::Vector2f(400.0, 250.0));
#pragma endregion

#pragma region Markers
	sf::RectangleShape rect;
	rect.setFillColor(sf::Color::Blue);
	rect.setSize(sf::Vector2f(20.0, 20.0));
	rect.setOrigin(sf::Vector2f(rect.getSize().x / 2, rect.getSize().y / 2));
#pragma endregion

	auto eg = make_enemy(EnemyType::Normal, window, grid);
	auto ea = make_enemy(EnemyType::Flying, window, grid);

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
#pragma region Drawing_markers
		window.clear(sf::Color(200, 200, 200));
		for (auto& item : grid.path)
		{
			rect.setPosition(item);
			window.draw(rect);
		}
#pragma endregion
		
		eg->update();
		ea->update();
		eg->render();
		ea->render();
		window.display();
	}

    return 0;
}
