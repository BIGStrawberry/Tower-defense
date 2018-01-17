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
	std::vector<sf::Vector2f> path;
	path.push_back(sf::Vector2f(0.0, 0.0));
	path.push_back(sf::Vector2f(100.0, 0.0));
	path.push_back(sf::Vector2f(100.0, 100.0));
	path.push_back(sf::Vector2f(275.0, 300.0));
	path.push_back(sf::Vector2f(400.0, 250.0));
#pragma endregion

#pragma region Markers
	sf::RectangleShape rect;
	rect.setFillColor(sf::Color::Blue);
	rect.setSize(sf::Vector2f(20.0, 20.0));
	rect.setOrigin(sf::Vector2f(rect.getSize().x / 2, rect.getSize().y / 2));
#pragma endregion

	auto eg = make_enemy(EnemyType::Normal, window, path);
	auto ea = make_enemy(EnemyType::Flying, window, path);

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
#pragma region Drawing_markers
		window.clear(sf::Color(200, 200, 200));
		for (auto& item : path)
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
		sf::Vector2f a = eg->getPosition();
	}

    return 0;
}
