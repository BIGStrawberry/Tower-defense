#include <SFML/Graphics.hpp>
#include "Tower/Tower.h"
#include "Enemy/make_enemy.h"


int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Project name");
	sf::Event event;
	Tower t(window, 10.0, sf::Vector2f(500, 200));
	
	//fakegrid
	Grid grid;
	grid.path.push_back(sf::Vector2f(0, 0));
	grid.path.push_back(sf::Vector2f(100, 0));
	grid.path.push_back(sf::Vector2f(100, 100));
	grid.path.push_back(sf::Vector2f(150, 200));

	std::vector<std::shared_ptr<Enemy>> enemies;
	enemies.push_back(make_enemy(EnemyType::Normal, window, grid));

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		for (auto& enemy : enemies) {
			enemy->update();
		}
		t.update();

		window.clear(sf::Color(200, 200, 200));

		for (auto& enemy : enemies) {
			enemy->render();
		}
		t.render();
		//

		window.display();
	}

	return 0;
}
