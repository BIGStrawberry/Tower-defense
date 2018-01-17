#include <SFML/Graphics.hpp>
#include "Grid.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Project name");
	sf::Event event;
	//TODO remove gridlines (tileSize + 1 ) => tileSize
	Grid grid(window, 31);

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear(sf::Color(200, 200, 200));
		grid.render();
		window.display();
	}

    return 0;
}
