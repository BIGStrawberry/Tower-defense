#include <SFML/Graphics.hpp>
#include "Tower/Tower.h"
#include "Enemy/make_enemy.h"


int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Project name");
	sf::Event event;
	window.setVerticalSyncEnabled(true);
	
	EnemyDataContainer::load();
	//fakegrid
	Grid grid;
	grid.path.push_back(sf::Vector2f(0.0f, 0.0f));
	grid.path.push_back(sf::Vector2f(100.0f, 0.0f));
	grid.path.push_back(sf::Vector2f(100.0f, 100.0f));
	grid.path.push_back(sf::Vector2f(150.0f, 200.0f));
	grid.path.push_back(sf::Vector2f(1280.0f, 720.0f));

	Tower t(window, 10, sf::Vector2f(500, 200), 150, grid, 1);
	Tower t2(window, 10, sf::Vector2f(500, 400), 150, grid, 1);

	grid.enemies.push_back(make_enemy(EnemyType::Normal, window, grid));

	/*auto e = make_enemy(EnemyType::Normal, window, grid);*/

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		for (auto& enemy : grid.enemies) {
			enemy->update();
		}
	
		t.update();
		t2.update();

		window.clear(sf::Color(200, 200, 200));

		for (auto& enemy : grid.enemies) {
			enemy->render();
		}
		t.render();
		t2.render();
		/*e->render();*/
		//

		window.display();
	}

	return 0;
}
