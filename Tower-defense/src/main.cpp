#include <SFML/Graphics.hpp>
#include "Tower/Tower.h"


int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Project name");
	sf::Event event;
	Tower t(window, 10.0, sf::Vector2f(500, 200));

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		t.update();

		window.clear(sf::Color(200, 200, 200));
		//
		t.render();
		//

		window.display();
	}

	return 0;
}
